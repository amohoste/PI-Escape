/***************************************************************
- Activation System -
Propageert de activatie van connectors. Er wordt een tijd 
bijgehouden om deze activatie stapsgewijs te laten verlopen.
****************************************************************/

#ifndef ACTIVATION_SYSTEM_H
#define ACTIVATION_SYSTEM_H
#define EMPTY_SYSTEM_STRUCT char c


typedef struct ActivationSystem {
	int step;
} ActivationSystem;

#include "../engine.h"

void system_activation_init(ActivationSystem*);
ActivationSystem* system_activation_alloc();
void system_activation_update(ActivationSystem*, Engine*);
void system_activation_free(ActivationSystem*);



#endif