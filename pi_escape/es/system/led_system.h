#ifndef LED_SYSTEM_H
#define LED_SYSTEM_H
#ifdef RPI
#define EMPTY_SYSTEM_STRUCT char c
#include "../engine.h"

typedef struct LedSystem {
	EMPTY_SYSTEM_STRUCT;
} LedSystem;


void system_led_init(LedSystem*);
LedSystem* system_led_alloc();
void system_led_update(LedSystem*, Engine*);
void system_led_free(LedSystem*);

#endif // RPI
#endif //LED_SYSTEM_H