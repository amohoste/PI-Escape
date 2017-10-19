#ifndef LPS25H
#define LPS25H

/*
	Initializeert een i2c adapter(0x5c)
	Initializeert calibratievariable
	@param frequentie aantal frequentie(hz) je door de lps25h sensor stuurt
		keuze tussen  0, 1, 7, 12, 25 bij een andere waarde 
		default 7
	@return 0 succeed, -1 failed
*/
int lps25h_init(int);

/*
	Lees de sensorwaarde in, calibreer
	@return druk in hPa
*/
int lps25h_read_pressure();

/*
	Lees de sensorwaarde in, calibreer
	@return temprature in � C
	   schrijf converters voor K en F als het nodig is
*/
int lps25h_read_temperature();


/*
	Een switch die de globale variable voor frequentie instelt
	@param frequentie in hexadecimaal
	@return 0;
*/
void init_initValue(frequentie);
#endif /* LPS25H */
