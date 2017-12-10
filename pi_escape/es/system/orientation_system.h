/***************************************************************
- Orientation System -
Afhandelen van IMU input (deel 2 van de opgave).
****************************************************************/

#ifndef ORIENTATION_SYSTEM_H
#define ORIENTATION_SYSTEM_H
#ifdef RPI

#include <stdint.h>
#include <glmc.h>

typedef float RTFLOAT;
typedef struct RTIMUDATA
{
	RTFLOAT x;
	RTFLOAT z;
} RTIMUDATA;

typedef struct RtImu RtImu;
typedef struct RtImuSetting RtImuSetting;

typedef struct OrientationSystem {
	RtImuSetting* rtimu_settings;
	RtImu* rtimu;
	RTIMUDATA rtimu_data;
	t_vec3 coord;
} OrientationSystem;

#include "../engine.h"

void system_orientation_init(OrientationSystem*);
OrientationSystem* system_orientation_alloc();
void system_orientation_update(OrientationSystem*, Engine*);
void system_orientation_free(OrientationSystem*);

#ifdef __cplusplus
extern "C" {
#include "RTIMULib.h"
#endif

	RtImuSetting* create_ImuSetting();
	void destroy_ImuSetting(RtImuSetting* settings);

	RtImu* create_RtImu(RtImuSetting* settings);
	void destroy_RtImu(RtImu* imu);
	void init_RtImu(RtImu* imu);
	int read_Imu(RtImu* imu);
	RTIMUDATA get_data(RtImu* imu);

#ifdef __cplusplus
}
#endif

#endif
#endif //ORIENTATION_SYSTEM_H