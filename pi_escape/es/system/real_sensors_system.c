#include "real_sensors_system.h"
#include "../../sensor/lps25h.h"
#include "../../sensor/hts221.h"
#include "../../sensor/i2c.h"

#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

RealSensorsSystem* system_real_sensors_alloc() {
    RealSensorsSystem* res = calloc(1, sizeof(RealSensorsSystem));
    system_real_sensors_init(res);
    return res;
}

void system_real_sensors_init(RealSensorsSystem* system) {
	system->humidity = calloc(1, sizeof(double));
	system->temperature = calloc(1, sizeof(double));
	system->pressure = calloc(1, sizeof(double));
}


void system_real_sensors_free(RealSensorsSystem* system) {
	free(system->humidity);
	free(system->temperature);
	free(system->pressure);
}

void system_real_sensors_update(RealSensorsSystem* system, Engine* engine) {
	double humidity = hts221_read_humidity();
	double temperature = hts221_read_temperature();
	double pressure = lps25h_read_pressure();
	system->humidity = &humidity;
	system->temperature = &temperature;
	system->pressure = &pressure;
}
