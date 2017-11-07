/***************************************************************
- Real Sensor System -

Haalt sensor data op via de functies gedeclareerd in de map 
../../sensor en update de overeenkomstige velden in de context.
****************************************************************/

#ifndef REAL_SENSORS_SYSTEM_H
#define REAL_SENSORS_SYSTEM_H
#ifdef RPI
#define EMPTY_SYSTEM_STRUCT char c

#include <stdint.h>

typedef struct RealSensorsSystem {
	EMPTY_SYSTEM_STRUCT;
} RealSensorsSystem;

#include "../engine.h"

#include "../../sensor/lps25h.h"
#include "../../sensor/hts221.h"
#include "../../sensor/i2c.h"

void system_real_sensors_init(RealSensorsSystem*);
RealSensorsSystem* system_real_sensors_alloc();
void system_real_sensors_update(RealSensorsSystem*, Engine*);
void system_real_sensors_free(RealSensorsSystem*);

#endif
#endif //REAL_SENSORS_SYSTEM_H
