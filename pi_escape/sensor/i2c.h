#ifndef I2C
#ifdef TARGET_LINUX_ARM
#define RPI

#include <stdint.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

/*
	Initializeert een i2c device
	en maakt het klaar om te communiceren met adres
	@param addr het adres voor communicatie
	@return file descriptor van i2c device
*/
int i2c_init_adapter(int);

/*
	Schrijf meegegeven data naar meegegeven register
	@param file de file descriptor
	@param reg de register waarop je schrijf
	@param data de data die je op het device wilt
	@return 0 succeed, -1 failed
*/
int i2c_write_byte_data(int, uint8_t , uint8_t );

/*
	Lees data in en return de data
	@param file de file descriptor
	@param reg de register waaruit je wilt lezen
	@return 0 succeed, -1 failed
*/
int i2c_read_byte_data(int, uint8_t);
#endif 
#endif /* I2C */