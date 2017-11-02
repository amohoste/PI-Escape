#ifdef RPI
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdio.h>

#include "../sensor/i2c.h"

#define FILENAME "/dev/i2c-1" // de naam van de "file" waarop de i2c bus bevinden

int i2c_init_adapter(int addr)
{
	int file = open(FILENAME, O_RDWR);

	/*if (Ioctl(file, I2C_SLAVE, addr) < 0) {
		return -1;
	}*/
	return file;
}

int i2c_write_byte_data(int file, uint8_t reg, uint8_t data)
{
	int returnValue = 0;
	char buff[2];
	buff[1] = reg;
	buff[2] = data;
	// In buff zitten 2 hexadecimale getallen dus 2 maal 1 byte
	if (write(file, buff, 2) != 2) {
		returnValue = -1;
	}
	return returnValue;
}

int i2c_read_byte_data(int file, uint8_t reg)
{
	char buff[1];
	buff[0] = reg;
	// eerst de register naar file schrijven en dan lees je het in
	if (write(file, buff, 1) != 1) {
		return -1;
	}
	if(read(file, buff, 1) != 1) {
		return -1;
	}
	return buff[0];
}
#endif