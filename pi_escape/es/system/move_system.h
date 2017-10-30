/***************************************************************
- Move System -
Zoekt entities met een MoveActionComponent, en voert de beweging 
uit indien mogelijk. Hierbij wordt rekening gehouden met 
animaties, en met de MoveHistoryComponent die de vorige beweging 
bijhoudt. Als twee pijltjestoetsen tegelijk ingedrukt worden, 
zal elke richting afwisselend gekozen worden om zo diagonaal 
te bewegen en langs muren te bewegen tot de eerste opening.
****************************************************************/

#ifndef MOVE_SYSTEM_H
#define MOVE_SYSTEM_H
#define EMPTY_SYSTEM_STRUCT char c


typedef struct MoveSystem {
	EMPTY_SYSTEM_STRUCT;
} MoveSystem;

#include "../engine.h"

void system_move_init(MoveSystem*);
MoveSystem* system_move_alloc();
void system_move_update(MoveSystem*, Engine*);
void system_move_free(MoveSystem*);

#endif //MOVE_SYSTEM_H
