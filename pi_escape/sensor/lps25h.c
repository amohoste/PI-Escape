#include "../sensor/lps25h.h"
#include "../sensor/i2c.h"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>


#define ADDR 0x5c
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define PRESS_OUT_XL 0x28
#define PRESS_OUT_L 0x29
#define PRESS_OUT_H 0x2A
#define TEMP_OUT_L 0x2B
#define TEMP_OUT_H 0x2C
#define CLEAN_START 0x20


int file;

int lps25h_init(int frequentie)
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
	
	return 0;
}

double lps25h_read_pressure()
{
	// bepalen van variablen
	uint8_t press_out_H = i2c_read_byte_data(file, PRESS_OUT_H);
	uint8_t press_out_L = i2c_read_byte_data(file, PRESS_OUT_L);
	uint8_t press_out_XL = i2c_read_byte_data(file, PRESS_OUT_XL);

	// variablen naar goed formaat omzetten
	uint32_t press_out_HLLX = press_out_H << 16 | press_out_L << 8 | press_out_XL;

	// pressure bepalen
	double pressure = press_out_HLLX / 4096.0;
	printf("Luchtdruk = %.0f", pressure);
	return pressure;
}

double lps25h_read_temperature()
{
	//ophalen van waarde
	uint8_t temp_out_L = i2c_read_byte_data(file, TEMP_OUT_L);
	uint8_t temp_out_H = i2c_read_byte_data(file, TEMP_OUT_H);

	// combinatie maken van h en l 
	uint16_t temp_out_HL = temp_out_H << 8 | temp_out_L;

	// bepalen van temperatuur in c
	double temp_C = 42.5 + (temp_out_HL / 480);
	printf("Temperatuur = %.2f°", temp_C);
	return temp_C;
}