#include "../sensor/lps25h.h"


/*
	Initializeert een i2c adapter(0x5c)
	Initializeert calibratievariable
	@param frequentie aantal frequentie(hz) je door de lps25h sensor stuurt
	@return 0 succeed, -1 failed 
*/
int lps25h_init(int frequentie)
{
	return 0;
}

/*
	Lees de sensorwaarde in, calibreer
	@return druk in hPa
*/
int lps25h_read_pressure()
{
	return 0;
}

/*
	Lees de sensorwaarde in, calibreer
	@return temprature in ° C
			schrijf converters voor K en F als het nodig is
*/
int lps25h_read_temperature()
{
	return 0;
}
