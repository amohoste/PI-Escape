#ifndef HTS221
#define HTS221

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
int hts221_read_humidity();

/*
	Lees de sensorwaarde in, calibreer
	@return temprature in ° C
	schrijf converters voor K en F als het nodig is
*/
int hts221_read_temperature();

/*
	Initialiseert calibratue 
*/
void init_calbration_value();
/*
	struct dat de calibratie waarden van temperatuur bevat
*/
typedef struct TempCali {
	uint8_t T0_degC;
	uint8_t T1_degC;
	int16_t T0_OUT;
	int16_t T1_OUT;
} TempCali;

/*
	struct dat de calibratie waarden van vochtigheid bevat
*/
typedef struct HumCali {
	uint8_t H0_rH;
	uint8_t H1_rH;
	int16_t H0_T0_OUT;
	int16_t H1_T0_OUT;
} HumCali;


#endif /* HTS221 */

