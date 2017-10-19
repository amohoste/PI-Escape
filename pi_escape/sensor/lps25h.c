#include "../sensor/lps25h.h"
#include "../sensor/i2c.h"

#include <stdint.h>
#include <linux/i2c-dev.h>

#define ADDR 0x5c
#define CTRL_REG1 0x20
#define PRESS_OUT_XL 0x28
#define PRESS_OUT_L 0x29
#define PRESS_OUT_H 0x2A
#define TEMP_OUT_L 0x2B
#define TEMP_OUT_H 0x2C

#define MAX_COUNT 20


int initValue = 0x80; // gewoon aanzetten en eenmalig op te minst 0x80 
int file;

int lps25h_init(int frequentie)
{
	uint8_t status = 0;
	uint8_t count = 0;

	// file maken
	file = i2c_init_adapter(ADDR);

	// kijken wat de keuze is voor de frequentie en de initValue bepalen
	init_initValue(frequentie);

	// configure slave
	if (ioctl(file, I2C_SLAVE, ADDR) < 0) {
		return -1;
	}

	// aanzetten van sensor en proberen te garanderen dat de sensor aanstaat
	do {
		usleep(10000);
		count++;
		status = i2c_write_byte_data(file, CTRL_REG1, initValue);
	} while (status != 0 && MAX_COUNT < count);
	if (count > MAX_COUNT) {
		return -1;
	}
	return 0;
}


int lps25h_read_pressure()
{
	// bepalen van variablen
	int press_out_H = i2c_read_byte_data(file, PRESS_OUT_H);
	int press_out_L = i2c_read_byte_data(file, PRESS_OUT_L);
	int press_out_XL = i2c_read_byte_data(file, PRESS_OUT_XL);

	// variablen naar goed formaat omzetten
	int press_out_HLLX = press_out_H << 16 | press_out_L << 8 | press_out_XL;

	// pressure bepalen
	return press_out_HLLX / 4096;
}


int lps25h_read_temperature()
{
	//ophalen van waarde
	int temp_out_H = i2c_read_byte_data(file, TEMP_OUT_H);
	int temp_out_L = i2c_read_byte_data(file, TEMP_OUT_L);

	// combinatie maken van h en l 
	// temp_out_h(=0025) word 2500 en | is de logische combinator
	int temp_out_HL = temp_out_H << 8 | temp_out_L;

	// bepalen van temperatuur in c
	return 42.5 + (temp_out_HL / 480);
}


void init_initValue(int frequentie) {
	switch (frequentie) {
	case 0:
		// eenmalige check
	case 7:
		initValue = 0xA0;
		break;
	case 12:
		initValue = 0xB0;
		break;
	case 25:
		initValue = 0xC0;
		break;
	default:
		initValue = 0x90;
	}
}
