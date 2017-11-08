#include "action_system.h"

#include <assert.h>

#include <stdlib.h>
#include "../assemblage.h"

ActionSystem* system_action_alloc() {
    ActionSystem* res = calloc(1, sizeof(ActionSystem));
    system_action_init(res);
    return res;
}

void system_action_init(ActionSystem* system) {
	system->prevAct = 0;
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
	// Todo: later anders als je kan opvragen op coordinaat
	Context* ctx = &(engine->context);
	Level* l = ctx->current_level;

	// Locatie speler opvragen
	EntityIterator player_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_INPUTRECEIVER, &player_it);
	next_entity(&player_it);
	EntityId player_entity_id = player_it.entity_id;
	assert(player_entity_id != NO_ENTITY);
	InputReceiverComponent* player_input = get_component(engine, player_entity_id, COMP_INPUTRECEIVER);
	
	if (player_input->actkey && system->prevAct == 0) {
		system->prevAct = 1;
		GridLocationComponent* player_grid_comp = get_component(engine, player_entity_id, COMP_GRIDLOCATION);
		int player_x = player_grid_comp->pos[0];
		int player_y = player_grid_comp->pos[1];

		// Alle componenten met itemactioncomponent zoeken (sleutels)
		EntityIterator itemaction_it;
		search_entity_1(engine, COMP_ITEMACTION, &itemaction_it);
		while (next_entity(&itemaction_it)) {
			EntityId itemaction_entity_id = itemaction_it.entity_id;
			assert(itemaction_entity_id != NO_ENTITY);

			// Oprapen als zelfde locatie speler heeft
			GridLocationComponent* item_grid_comp = get_component(engine, itemaction_entity_id, COMP_GRIDLOCATION);
			int key_x = item_grid_comp->pos[0];
			int key_y = item_grid_comp->pos[1];


			if (key_x == player_x && key_y == player_y) {

				if (!has_component(engine, itemaction_entity_id, COMP_INCONTAINER)) {
					create_component(engine, itemaction_entity_id, COMP_INCONTAINER);
				}
				else {
					// Kijken of niet op locatie van deur is
					// TODO: later anders
					if (!(IS_DOOR(key_x, key_y))) {
						free_component(engine, itemaction_entity_id, COMP_INCONTAINER);
					}
				}

			}
		}
	}
	else if (!player_input->actkey && system->prevAct == 1) {
		system->prevAct = 0;
	}
	
}
