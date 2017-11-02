/***************************************************************
- Endlevel System -
Gaat na of de speler de uitgang heeft bereikt (speler heeft 
zelfde posities als entity met een ExitComponent). Indien de
uitgang bereikt is, start de exit animatie. Na deze animatie 
wordt de context aangepast zodat het level eindigt.
****************************************************************/

#ifndef ENDLEVEL_SYSTEM_H
#define ENDLEVEL_SYSTEM_H
#define EMPTY_SYSTEM_STRUCT char c


typedef struct EndLevelSystem {
	EMPTY_SYSTEM_STRUCT;
} EndLevelSystem;

#include "../engine.h"

#define EXIT_ANIMATION_DURATION_MS 1500

void system_endlevel_init(EndLevelSystem*);
EndLevelSystem* system_endlevel_alloc();
void system_endlevel_update(EndLevelSystem*, Engine*);
void system_endlevel_free(EndLevelSystem*);


#endif //ENDLEVEL_SYSTEM_H