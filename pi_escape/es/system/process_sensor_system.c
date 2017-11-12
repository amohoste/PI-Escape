#include "process_sensor_system.h"
#include "../../../util/rgb_triple.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

ProcessSensorSystem* system_process_sensor_alloc() {
    ProcessSensorSystem* res = calloc(1, sizeof(ProcessSensorSystem));
    system_process_sensor_init(res);
    return res;
}

void system_process_sensor_init(ProcessSensorSystem* system) {
	system->humidity = 0;
	system->pressure = 0;
	system->temperature = 0;
}

void system_process_sensor_free(ProcessSensorSystem* system) {
    // Not used
}

void system_process_sensor_update(ProcessSensorSystem* system, Engine* engine) {
	// reduce change by checking if the value changed
	if (system->humidity != (engine->context.humidity))
	{
		system->humidity = (engine->context.humidity);
		engine->context.wall_color[0] = ((sin(0.3 * system->humidity) * 127) + 128) / 256;
		engine->context.wall_color[1] = ((sin((0.3 * system->humidity) + (2 * PI / 3)) * 127) + 128) / 256;
		engine->context.wall_color[2] = ((sin((0.3 * system->humidity) + (4 * PI / 3)) * 127) + 128) / 256;
	}
	if (system->pressure != (engine->context.pressure))
	{
		system->pressure = (engine->context.pressure);
		engine->context.floor_color[0] = ((sin(0.3 * system->pressure) * 127) + 128) / 256;
		engine->context.floor_color[1] = ((sin((0.3 * system->pressure) + (2 * PI / 3)) * 127) + 128) / 256;
		engine->context.floor_color[2] = ((sin((0.3 * system->pressure) + (4 * PI / 3)) * 127) + 128) / 256;
	}
	if (system->temperature != (engine->context.temperature))
	{
		system->temperature = (engine->context.temperature);
		engine->context.world_color[0] = sin((0.3 * system->temperature));
		engine->context.world_color[1] = sin((0.3 * system->temperature) + (2 * PI / 3));
		engine->context.world_color[2] = sin((0.3 * system->temperature) + (4 * PI / 3));
	}
}

