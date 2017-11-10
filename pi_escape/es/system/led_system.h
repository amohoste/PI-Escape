#ifndef LED_SYSTEM_H
#define LED_SYSTEM_H
#ifdef RPI
#define EMPTY_SYSTEM_STRUCT char c

typedef struct LedSystem {
	EMPTY_SYSTEM_STRUCT;
} LedSystem;

#include "../engine.h"

void system_led_init(LedSystem*);
LedSystem* system_led_alloc();
void system_led_update(LedSystem*, Engine*);
void system_led_free(LedSystem*);

#endif // RPI
#endif //LED_SYSTEM_H