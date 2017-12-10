#ifdef RPI
#include "../es/system/orientation_system.h"
#include "RTIMULibDefs.h"


RtImuSetting* create_ImuSetting() {
	return reinterpret_cast<RtImuSetting*>(new RTIMUSettings("RTIMULib"));
}

void destroy_ImuSetting(RtImuSetting* struc) {
	delete reinterpret_cast<RTIMUSettings*>(struc);
}

void destroy_RtImu(RtImu* struc) {
	delete reinterpret_cast<RTIMU*>(struc);
}

RtImu* create_RtImu(RtImuSetting* settings) {
	return reinterpret_cast<RtImu*>(RTIMU::createIMU(reinterpret_cast<RTIMUSettings*>(settings)));
}

void init_RtImu(RtImu* imu) {
	reinterpret_cast<RTIMU*>(imu)->IMUInit();
}

int read_Imu(RtImu* imu) {
	return reinterpret_cast<RTIMU*>(imu)->IMURead();
}

RTIMUDATA get_data(RtImu* imu) {
	RTIMUDATA rtimu_data;
	RTIMU_DATA data = reinterpret_cast<RTIMU*>(imu)->getIMUData();
	rtimu_data.x = data.fusionPose.x();
	rtimu_data.z = data.fusionPose.z();
	return rtimu_data;
}

#endif // RPI