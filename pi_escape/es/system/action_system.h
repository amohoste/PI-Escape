 /***************************************************************
- Action System - 
Zoekt naar entities met een ItemActionComponent component,
en voert de actie uit indien mogelijk (oprapen, neerleggen,
of verwisselen van de sleutel). Er wordt hiervoor gekeken of
op dezelfde locatie (GridLocationComponent) als een entity met
een ContainerComponent en een ItemActionComponent een andere
entity is die een ItemComponent heeft. De InContainerComponent
wordt dan aangepast (verwijderd of toegevoegd).
****************************************************************/

#ifndef ACTION_SYSTEM_H
#define ACTION_SYSTEM_H
#define EMPTY_SYSTEM_STRUCT char c

typedef struct ActionSystem {
	EMPTY_SYSTEM_STRUCT;
} ActionSystem;

#include "../engine.h"

void system_action_init(ActionSystem*);
ActionSystem* system_action_alloc();
void system_action_update(ActionSystem*, Engine*);
void system_action_free(ActionSystem*);

#endif
