/***************************************************************
- Animation System -
Beheert de timing van de animaties, en verwijdert 
de animaties wanneer ze voltooid zijn.
****************************************************************/

#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H
#define EMPTY_SYSTEM_STRUCT char c


typedef struct AnimationSystem {
	EMPTY_SYSTEM_STRUCT;
} AnimationSystem;

#include "../engine.h"

void system_animation_init(AnimationSystem*);
AnimationSystem* system_animation_alloc();
void system_animation_update(AnimationSystem*, Engine*);
void system_animation_free(AnimationSystem*);



#endif