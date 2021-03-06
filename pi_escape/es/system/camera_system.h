/***************************************************************
- Camera System -
Bepaalt hoe de camera gepositioneerd is, en zorgt dat
de camera niet te snel van positie verandert.
****************************************************************/

#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H
#define EMPTY_SYSTEM_STRUCT char c

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

#define CAMERA_PERCENT_SPEED_PER_S 200.0f
#define CAMERA_MIN_SPEED_PER_TICK 0.05f

typedef struct CameraSystem {
	EMPTY_SYSTEM_STRUCT;
} CameraSystem;

#include "../engine.h"

void system_camera_init(CameraSystem*);
CameraSystem* system_camera_alloc();
void system_camera_update(CameraSystem*, Engine*);
void system_camera_free(CameraSystem*);


#endif //CAMERA_SYSTEM_H