#ifndef HTS221
#define HTS221
#ifdef RPI

#include <stdint.h>


/*
	Initializeert een i2c adapter(0x5f)
	Initializeert calibratievariable
	@param frequentie aantal frequentie(hz) je door de hts221 sensor stuurt
	@return 0 succeed, -1 failed
*/
int hts221_init(int);

/*
	Lees de sensorwaarde in, calibreer
	@return relative humidity
*/
double hts221_read_humidity();

/*
	Lees de sensorwaarde in, calibreer
	@return temprature in ° C
	schrijf converters voor K en F als het nodig is
*/
double hts221_read_temperature();


/*
	struct dat de calibratie waarden van temperatuur bevat
*/
typedef struct TemperatureC{
	uint8_t t0_degC_x8;
	uint8_t t1_degC_x8;
	uint8_t t1_t0_msb;
} TemperatureC;

/*
	struct dat de calibratie waarden van vochtigheid bevat
*/
typedef struct HumidityLSB{
	uint8_t h0_out_l;
	uint8_t h0_out_h;
	uint8_t h1_out_l;
	uint8_t h1_out_h;
} HumidityLSB;

typedef struct TemperatureLSB {
	uint8_t t0_out_l;
	uint8_t t0_out_h;
	uint8_t t1_out_l;
	uint8_t t1_out_h;
} TemperatureLSB;

typedef struct Temperature {
	double temp_C;
} Temperature;

typedef struct Humidity {
	double humidity;
} Humidity;

/*
	Een switch die de globale variable voor frequentie instelt
	@param frequentie in hexadecimaal
*/
#endif /* HTS221 */
#endif