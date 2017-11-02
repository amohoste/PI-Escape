#ifndef REAL_SENSORS_SYSTEM_H
#define REAL_SENSORS_SYSTEM_H

#include <stdint.h>

typedef struct RealSensorsSystem {
	double* temperature;
	double* pressure;
	double* humidity;
} RealSensorsSystem;

#include "../engine.h"

void system_real_sensors_init(RealSensorsSystem*);
RealSensorsSystem* system_real_sensors_alloc();
void system_real_sensors_update(RealSensorsSystem*, Engine*);
void system_real_sensors_free(RealSensorsSystem*);

#endif //REAL_SENSORS_SYSTEM_H
