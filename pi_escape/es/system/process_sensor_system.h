/******************************************************************
- Process Sensor System -

Bepaalt aan de hand van de velden in context de kleuren voor de 
achtergrond, de muren en de vloeren, deze velden worden ingevult  
door real sensor system(in het geval RPI) ander door input system.
******************************************************************/

#ifndef PROCESS_SENSOR_SYSTEM_H
#define PROCESS_SENSOR_SYSTEM_H

#include <stdint.h>

#include "../../../util/rgb_triple.h"

typedef struct ProcessSensorSystem {
	double humidity;
	double pressure;
	double temperature;
} ProcessSensorSystem;

#include "../engine.h"

void system_process_sensor_init(ProcessSensorSystem*);
ProcessSensorSystem* system_process_sensor_alloc();
void system_process_sensor_update(ProcessSensorSystem*, Engine*);
void system_process_sensor_free(ProcessSensorSystem*);


#endif //PROCESS_SENSOR_SYSTEM_H