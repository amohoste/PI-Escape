#ifdef RPI

#include <unistd.h>
#include <stdio.h>

#include "hts221.h"
#include "i2c.h"

#define ADDR 0x5f
#define CTRL_REG1 0x20
#define CTRL_REG3 0x22
#define STATUS_REG 0x27

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
#define CLEAN_START 0x20
#define START_VALUE 0x80

Hts221 hts221;

int hts221_init(int frequentie)
{
	uint8_t status;
	if (frequentie > 3 && frequentie < 0) {
		frequentie = 2;
	}

	// file maken en configureer de slave
	if ((hts221.filehts221 = i2c_init_adapter(ADDR)) == -1) {
		return -1;
	}

	i2c_write_byte_data(hts221.filehts221, CTRL_REG1, CLEAN_START);

	i2c_write_byte_data(hts221.filehts221, CTRL_REG1, START_VALUE | frequentie);

	i2c_write_byte_data(hts221.filehts221, CTRL_REG3, 0x01);
	do {
		usleep(2500);
		status = i2c_read_byte_data(hts221.filehts221, STATUS_REG);
	} while (status != 0);

	hts221.t0_degC_x8 = i2c_read_byte_data(hts221.filehts221, T0_degC_x8);
	hts221.t1_degC_x8 = i2c_read_byte_data(hts221.filehts221, T1_degC_x8);
	hts221.t1_t0_msb = i2c_read_byte_data(hts221.filehts221, T1_T0_MSB);
	
	hts221.t0_out_l = i2c_read_byte_data(hts221.filehts221, T0_OUT_L);
	hts221.t0_out_h = i2c_read_byte_data(hts221.filehts221, T0_OUT_H);
	hts221.t1_out_l = i2c_read_byte_data(hts221.filehts221, T1_OUT_L);
	hts221.t1_out_h = i2c_read_byte_data(hts221.filehts221, T1_OUT_H);

	hts221.h0_out_l = i2c_read_byte_data(hts221.filehts221, H0_T0_OUT_L);
	hts221.h0_out_h = i2c_read_byte_data(hts221.filehts221, H0_T0_OUT_H);
	hts221.h1_out_l = i2c_read_byte_data(hts221.filehts221, H1_T0_OUT_L);
	hts221.h1_out_h = i2c_read_byte_data(hts221.filehts221, H1_T0_OUT_H);

	hts221.humidity = -9999;
	hts221.temp_C = -9999;

	return 0;
}

double hts221_read_humidity()
{
	int status = i2c_read_byte_data(hts221.filehts221, STATUS_REG);
	if ((status == 0 ||status == 2) && hts221.humidity != -9999) {
		return hts221.humidity;
	}

	uint8_t h_t_out_l = i2c_read_byte_data(hts221.filehts221, H_T_OUT_L);
	uint8_t h_t_out_h = i2c_read_byte_data(hts221.filehts221, H_T_OUT_H);

	double H0_rH = i2c_read_byte_data(hts221.filehts221, H0_rH_x2) / 2.0;
	double H1_rH = i2c_read_byte_data(hts221.filehts221, H1_rH_x2) / 2.0;

	int16_t H0_T0_OUT = hts221.h0_out_h << 8 | hts221.h0_out_l;
	int16_t H1_T0_OUT = hts221.h1_out_h << 8 | hts221.h1_out_l;

	double h_m = (H1_rH - H0_rH) / (H1_T0_OUT - H0_T0_OUT);
	double h_c = H1_rH - (h_m * H1_T0_OUT);

	/* make 16 bit value */
	int16_t H_T_OUT = h_t_out_h << 8 | h_t_out_l;

	hts221.humidity = (h_m * H_T_OUT) + h_c;
	return hts221.humidity;
}

double hts221_read_temperature()
{
	int status = i2c_read_byte_data(hts221.filehts221, STATUS_REG);
	if ((status == 0 || status == 1) && hts221.temp_C != -9999) {
		return hts221.temp_C;
	}
	uint8_t t_out_l = i2c_read_byte_data(hts221.filehts221, TEMP_OUT_L);
	uint8_t t_out_h = i2c_read_byte_data(hts221.filehts221, TEMP_OUT_H);

	double T0_DegC = ((hts221.t1_t0_msb & 3) << 8 | hts221.t0_degC_x8) / 8.0;
	double T1_DegC = (((hts221.t1_t0_msb & 12) >> 2) << 8 | hts221.t1_degC_x8) / 8.0;

	int16_t T0_out = hts221.t0_out_h << 8 | hts221.t0_out_l;
	int16_t T1_out = hts221.t1_out_h << 8 | hts221.t1_out_l;

	double t_m = (T1_DegC - T0_DegC) / (T1_out - T0_out);
	double t_c = T1_DegC - (t_m * T1_out);

	int16_t T_out = t_out_h << 8 | t_out_l;

	hts221.temp_C = (t_m * T_out) + t_c;
	return hts221.temp_C;
}	
#endif // RPI