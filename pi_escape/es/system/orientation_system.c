#ifdef RPI
#include "orientation_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>


OrientationSystem* system_orientation_alloc() {
	OrientationSystem* res = calloc(1, sizeof(OrientationSystem));
	system_orientation_init(res);
	return res;
}

void system_orientation_init(OrientationSystem* system) {
	system->rtimu_settings = create_ImuSetting();
	system->rtimu = create_RtImu(system->rtimu_settings);
	init_RtImu(system->rtimu);
}


void system_orientation_free(OrientationSystem* system) {
	destroy_ImuSetting(system->rtimu_settings);
	destroy_RtImu(system->rtimu);
}

void system_orientation_update(OrientationSystem* system, Engine* engine) {
	if (read_Imu(system->rtimu)) {
		RTIMUDATA newRead = get_data(system->rtimu);
		if (newRead.x != system->rtimu_data.x || newRead.z != system->rtimu_data.z) {
			system->rtimu_data = newRead;
			CameraLookAtComponent *cameralookat = search_first_component(engine, COMP_CAMERA_LOOK_AT);
			CameraLookFromComponent *cameralookfrom = search_first_component(engine, COMP_CAMERA_LOOK_FROM);
			float cur_x = system->rtimu_data.x;
			float cur_z = system->rtimu_data.z;
			system->coord[0] = (float)(cos(cur_x) * 10 + cameralookat->pos[0]);
			system->coord[1] = (float)(cos(cur_z) * sin(cur_x) * 10 + cameralookat->pos[1]);
			system->coord[2] = (float)(sin(cur_z) * 10 + cameralookat->pos[2]);
			glmc_vec3_set(cameralookfrom->pos, system->coord[0], system->coord[1], system->coord[2]);
		}
	}
}
#endif