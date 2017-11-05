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
	// Sleutel omhoog getekend als InContainerComponent* container = get_component(engine, drawable_entity_id, COMP_INCONTAINER); != null
	/*
	EntityIterator player_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_INPUTRECEIVER, &player_it);
	next_entity(&player_it);
	EntityId player_entity_id = player_it.entity_id;
	assert(player_entity_id != NO_ENTITY);
	t_ivec2 player_grid_pos;
	GridLocationComponent* player_grid_comp = get_component(engine, player_entity_id, COMP_GRIDLOCATION);
	*/

	EntityIterator itemaction_it;
	search_entity_1(engine, COMP_ITEMACTION, &itemaction_it);
	
}
