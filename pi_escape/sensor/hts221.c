#include "../sensor/hts221.h"


/*
	Initializeert een i2c adapter(0x5f)
	Initializeert calibratievariable
	@param frequentie aantal frequentie(hz) je door de hts221 sensor stuurt
	@return 0 succeed, -1 failed 
*/
int hts221_init(int frequentie)
{
	return 0;
}

/*
	Lees de sensorwaarde in, calibreer 
	@return relative humidity
*/
int hts221_read_humidity()
{
	return 0;
}

/*
	Lees de sensorwaarde in, calibreer
	@return temprature in ° C 
        schrijf converters voor K en F als het nodig is
*/
int hts221_read_temperature()
{
	return 0;
}	
