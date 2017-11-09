#ifdef RPI

#include <unistd.h>

#include "../sensor/lps25h.h"
#include "../sensor/i2c.h"

#define ADDR 0x5c
#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define PRESS_OUT_XL 0x28
#define PRESS_OUT_L 0x29
#define PRESS_OUT_H 0x2A
#define TEMP_OUT_L 0x2B
#define TEMP_OUT_H 0x2C
#define CLEAN_START 0x20
#define START_VALUE 0x80


int filelps25h;

int lps25h_init(int frequentie)
{
	uint8_t status;
	if (frequentie > 4 && frequentie < 0) {
		frequentie = 2;
	}

	// file maken en configureer de slave
	if ((filelps25h = i2c_init_adapter(ADDR)) == -1) {
		return -1;
	}
	i2c_write_byte_data(filelps25h, CTRL_REG1, CLEAN_START);

	i2c_write_byte_data(filelps25h, CTRL_REG1, START_VALUE | frequentie << 4);

	i2c_write_byte_data(filelps25h, CTRL_REG4, 0x01);
	do {
		usleep(2500);
		status = i2c_read_byte_data(filelps25h, CTRL_REG4);
	} while (status != 0);
	
	return 0;
}

double lps25h_read_pressure()
{
	// bepalen van variablen
	uint8_t press_out_H = i2c_read_byte_data(filelps25h, PRESS_OUT_H);
	uint8_t press_out_L = i2c_read_byte_data(filelps25h, PRESS_OUT_L);
	uint8_t press_out_XL = i2c_read_byte_data(filelps25h, PRESS_OUT_XL);

	// variablen naar goed formaat omzetten
	int32_t press_out_HLLX = press_out_H << 16 | press_out_L << 8 | press_out_XL;

	// pressure bepalen
	double pressure = press_out_HLLX / 4096.0;
	return pressure;
}

double lps25h_read_temperature()
{
	//ophalen van waarde
	// TODO vraag of dit klopt
	uint8_t temp_out_L = i2c_read_byte_data(filelps25h, TEMP_OUT_L);
	uint8_t temp_out_H = i2c_read_byte_data(filelps25h, TEMP_OUT_H);

	// combinatie maken van h en l 
	int16_t temp_out_HL = temp_out_H << 8 | temp_out_L;

	// bepalen van temperatuur in c
	double temp_C = 42.5 + (temp_out_HL / 480.0);
	return temp_C;
}

#endif