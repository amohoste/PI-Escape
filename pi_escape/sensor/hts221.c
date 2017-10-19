#include "../sensor/hts221.h"
#include "../sensor/i2c.h"

#include <stdint.h>
#include <linux/i2c-dev.h>

#define ADDR 0x5f
#define CTRL_REG1 0x20

#define H0_RH_X2 0x30
#define H1_RH_X2 0x31
#define H0_T0_OUT_L 0x36
#define H0_T0_OUT_H 0x37
#define H1_T0_OUT_L 0x3A
#define H1_T0_OUT_H 0x3B

#define T0_DEGC_X8 0x32
#define T1_DEGC_X8 0x33
#define T0_OUT_L 0x3C
#define T0_OUT_H 0x3D
#define T1_OUT_L 0x3E
#define T1_OUT_H 0x3F

#define TEMP_OUT_L 0x2A
#define TEMP_OUT_H 0x2B
#define HUM_OUT_L 0x28
#define HUM_OUT_H 0x29

#define MAX_COUNT 20


int initValue = 55555555; // gewoon aanzetten en eenmalig op te minst 0x80 
int file;
TempCali tempCali;
HumCali humCali;

int hts221_init(int frequentie)
{
	int status = 0;
	int count = 0;

	file = i2c_init_adapter(ADDR);
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

	init_calbration_value();

	return 0;
}


int hts221_read_humidity()
{
	// bepalen van variablen
	int hum_out_H = i2c_read_byte_data(file, HUM_OUT_H);
	int hum_out_L = i2c_read_byte_data(file, HUM_OUT_L);

	int hum_out_HL = hum_out_H << 8 | hum_out_L;

	int temp = (humCali.H1_rH - humCali.H0_rH) * (hum_out_HL - humCali.H0_T0_OUT);
	return (temp / (humCali.H1_T0_OUT - humCali.H0_T0_OUT)) + humCali.H0_rH;
}


int hts221_read_temperature()
{
	int temp_out_H = i2c_read_byte_data(file, TEMP_OUT_H);
	int temp_out_L = i2c_read_byte_data(file, TEMP_OUT_L);

	int temp_out_HL = temp_out_H << 8 | temp_out_L;

	int temp = (tempCali.T1_degC - tempCali.T.0_degC) * (temp_out_HL - tempCali.T0_OUT);
	return (temp / (tempCali.T0_OUT - tempCali.T1_OUT)) + tempCali.T0_degC;
}	

void init_calbration_value() 
{
	humCali.H0_rH = i2c_read_byte_data(file, H0_RH_X2) / 2;
	humCali.H1_rH = i2c_read_byte_data(file, H1_RH_X2) / 2;
	humCali.H0_T0_OUT = i2c_read_byte_data(file, H0_T0_OUT_H) << 8 | i2c_read_byte_data(file, H0_T0_OUT_L);
	humCali.H1_T0_OUT = i2c_read_byte_data(file, H1_T0_OUT_H) << 8 | i2c_read_byte_data(file, H1_T0_OUT_L);

	// Misschien error bij negatieve getallen!
	tempCali.T0_degC = i2c_read_byte_data(file, T0_DEGC_X8) / 8;
	tempCali.T1_degC = i2c_read_byte_data(file, T1_DEGC_X8) / 8;
	tempCali.T0_OUT = i2c_read_byte_data(file, T0_OUT_H) << 8 | i2c_read_byte_data(file, T0_OUT_L);
	tempCali.T1_OUT = i2c_read_byte_data(file, T1_OUT_H) << 8 | i2c_read_byte_data(file, T1_OUT_L);
}