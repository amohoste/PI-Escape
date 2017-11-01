#include "../sensor/hts221.h"
#include "../sensor/i2c.h"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#define ADDR 0x5f
#define CLEAN_START 0x20

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21

#define T0_OUT_L 0x3C
#define T0_OUT_H 0x3D
#define T1_OUT_L 0x3E
#define T1_OUT_H 0x3F
#define T0_degC_x8 0x32
#define T1_degC_x8 0x33
#define T1_T0_MSB 0x35

#define TEMP_OUT_L 0x2A
#define TEMP_OUT_H 0x2B

#define H0_T0_OUT_L 0x36
#define H0_T0_OUT_H 0x37
#define H1_T0_OUT_L 0x3A
#define H1_T0_OUT_H 0x3B
#define H0_rH_x2 0x30
#define H1_rH_x2 0x31

#define H_T_OUT_L 0x28
#define H_T_OUT_H 0x29


int file;
TemperatureC tempC;
TemperatureLSB tempLSB;
HumidityLSB humLSB;

int hts221_init(int frequentie)
{
	uint8_t status;

	// file maken en configureer de slave
	if ((file = i2c_init_adapter(ADDR)) == -1) {
		close(file);
		return -1;
	}

	i2c_write_byte_data(file, CTRL_REG1, CLEAN_START);

	//TODO: change 0x84 to frequentie
	i2c_write_byte_data(file, CTRL_REG1, 0x84);

	i2c_write_byte_data(file, CTRL_REG2, 0x01);

	do {
		sleep(2500);
		status = i2c_read_byte_data(file, CTRL_REG2);
	} while (status != 0);

	tempC.t0_degC_x8 = i2c_read_byte_data(file, T0_degC_x8);
	tempC.t1_degC_x8 = i2c_read_byte_data(file, T1_degC_x8);
	tempC.t1_t0_msb = i2c_read_byte_data(file, T1_T0_MSB);
	
	tempLSB.t0_out_l = i2c_read_byte_data(file, T0_OUT_L);
	tempLSB.t0_out_h = i2c_read_byte_data(file, T0_OUT_H);
	tempLSB.t1_out_l = i2c_read_byte_data(file, T1_OUT_L);
	tempLSB.t1_out_h = i2c_read_byte_data(file, T1_OUT_H);

	humLSB.h0_out_l = i2c_read_byte_data(file, H0_T0_OUT_L);
	humLSB.h0_out_h = i2c_read_byte_data(file, H0_T0_OUT_H);
	humLSB.h1_out_l = i2c_read_byte_data(file, H1_T0_OUT_L);
	humLSB.h1_out_h = i2c_read_byte_data(file, H1_T0_OUT_H);

	return 0;
}

double hts221_read_humidity()
{
	int16_t H0_T0_OUT = humLSB.h0_out_h << 8 | humLSB.h0_out_l;
	int16_t H1_T0_OUT = humLSB.h1_out_h << 8 | humLSB.h1_out_l;

	double H0_rH = i2c_read_byte_data(file, H0_rH_x2) / 2.0;
	double H1_rH = i2c_read_byte_data(file, H1_rH_x2) / 2.0;

	double h_m = (H1_rH - H0_rH) / (H1_T0_OUT - H0_T0_OUT);
	double h_c = H1_rH - (h_m * H1_T0_OUT);

	uint8_t h_t_out_l = i2c_read_byte_data(file, H_T_OUT_L);
	uint8_t h_t_out_h = i2c_read_byte_data(file, H_T_OUT_H);

	/* make 16 bit value */
	int16_t H_T_OUT = h_t_out_h << 8 | h_t_out_l;

	double humidity = (h_m * H_T_OUT) + h_c;
	printf("Luchtvochtigheid = %.2f°", humidity);
	return humidity;
}

double hts221_read_temperature()
{
	int16_t T0_out = tempLSB.t0_out_h << 8 | tempLSB.t0_out_l;
	int16_t T1_out = tempLSB.t1_out_h << 8 | tempLSB.t1_out_l;

	double T0_DegC = ((tempC.t1_t0_msb & 3) << 8 | tempC.t0_degC_x8) / 8.0;
	double T1_DegC = (((tempC.t1_t0_msb & 12) >> 2) << 8 | tempC.t1_degC_x8) / 8.0;

	double t_m = (T1_DegC - T0_DegC) / (T1_out - T0_out);
	double t_c = T1_DegC - (t_m * T1_out);

	uint8_t t_out_l = i2c_read_byte_data(file, TEMP_OUT_L);
	uint8_t t_out_h = i2c_read_byte_data(file, TEMP_OUT_H);

	int16_t T_out = t_out_h << 8 | t_out_l;

	double temp_C = (t_m * T_out) + t_c;
	printf("Temperatuur = %.2f°", temp_C);
	return temp_C;
}	