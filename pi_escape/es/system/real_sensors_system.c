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
	system->humidity = calloc(1, sizeof(int));
	system->temperature = calloc(1, sizeof(int));
	system->pressure = calloc(1, sizeof(int));
}


void system_real_sensors_free(RealSensorsSystem* system) {
	free(system->humidity);
	free(system->temperature);
	free(system->pressure);
	free(system);
}

void system_real_sensors_update(RealSensorsSystem* system, Engine* engine) {
	system->humidity = hts221_read_humidity();
	system->temperature = hts221_read_temperature();
	system->pressure = lps25h_read_pressure();
}
