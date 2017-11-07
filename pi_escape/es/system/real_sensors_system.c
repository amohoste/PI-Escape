#include "real_sensors_system.h"

#ifdef RPI
#include "../../sensor/lps25h.h"
#include "../../sensor/hts221.h"
#include "../../sensor/i2c.h"
#endif // RPI

#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

#define FREQUENCY 2;

RealSensorsSystem* system_real_sensors_alloc() {
    RealSensorsSystem* res = calloc(1, sizeof(RealSensorsSystem));
    system_real_sensors_init(res);
    return res;
}

void system_real_sensors_init(RealSensorsSystem* system) {
#ifdef RPI
		hts221_init(FREQUENCY);
		lps25h_init(FREQUENCY);
#endif // RPI
}


void system_real_sensors_free(RealSensorsSystem* system) {
}

void system_real_sensors_update(RealSensorsSystem* system, Engine* engine) {
#ifdef RPI
	engine->context.humidity = hts221_read_humidity();
	engine->context.temperature = hts221_read_temperature();
	engine->context.pressure = lps25h_read_pressure();
#endif // RPI
}
