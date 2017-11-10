#include "container_system.h"


#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

ContainerSystem* system_container_alloc() {
    ContainerSystem* res = calloc(1, sizeof(ContainerSystem));
    system_container_init(res);
    return res;
}

void system_container_init(ContainerSystem* system) {
    //TODO
}


void system_container_free(ContainerSystem* system) {
    //TODO
}

void system_container_update(ContainerSystem* system, Engine* engine) {
    //TODO

	// Locatie speler opvragen
	EntityIterator player_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_INPUTRECEIVER, &player_it);
	next_entity(&player_it);
	EntityId player_entity_id = player_it.entity_id;
	assert(player_entity_id != NO_ENTITY);
	GridLocationComponent* player_grid_comp = get_component(engine, player_entity_id, COMP_GRIDLOCATION);
	int player_x = player_grid_comp->pos[0];
	int player_y = player_grid_comp->pos[1];

	// Alle entities met incontainercomponent locatie speler geven
	EntityIterator incontainer_it;
	search_entity_1(engine, COMP_INCONTAINER, &incontainer_it);
	while (next_entity(&incontainer_it)) {
		EntityId incontainer_entity_id = incontainer_it.entity_id;
		assert(incontainer_entity_id != NO_ENTITY);

		GridLocationComponent* item_grid_comp = get_component(engine, incontainer_entity_id, COMP_GRIDLOCATION);
		update_location(item_grid_comp->pos[0], item_grid_comp->pos[1], engine, incontainer_entity_id, player_x, player_y);
	}

}
