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

#include "action_system.h"

#include <assert.h>

#include <stdlib.h>

ActionSystem* system_action_alloc() {
    ActionSystem* res = calloc(1, sizeof(ActionSystem));
    system_action_init(res);
    return res;
}

void system_action_init(ActionSystem* system) {
    //TODO
}


void system_action_free(ActionSystem* system) {
    //TODO
}

void system_action_update(ActionSystem* system, Engine* engine) {
    //TODO
}
