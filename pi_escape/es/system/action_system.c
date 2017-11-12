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
	// Locatie speler opvragen
	EntityIterator player_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_INPUTRECEIVER, &player_it);
	
	while (next_entity(&player_it)) {
		EntityId player_entity_id = player_it.entity_id;
		assert(player_entity_id != NO_ENTITY);
		InputReceiverComponent* player_input = get_component(engine, player_entity_id, COMP_INPUTRECEIVER);

		if (player_input->actkey && system->prevAct == 0) {
			system->prevAct = 1;
			GridLocationComponent* player_grid_comp = get_component(engine, player_entity_id, COMP_GRIDLOCATION);
			int player_x = player_grid_comp->pos[0];
			int player_y = player_grid_comp->pos[1];

			EntityListIterator key_it;
			start_search_in_list(player_x, player_y, engine, &key_it);
			add_component_constraint(&key_it, 1, COMP_ITEMACTION);

			while (next_in_list_mask(&key_it)) {
				EntityId itemaction_entity_id = key_it.entity_id;
				assert(itemaction_entity_id != NO_ENTITY);

				if (!has_component(engine, itemaction_entity_id, COMP_INCONTAINER)) {
					create_component(engine, itemaction_entity_id, COMP_INCONTAINER);
				}
				else {
					// Kijken of we niet op deur neerzetten
					EntityListIterator door_it;
					start_search_in_list(player_x, player_y, engine, &door_it);
					add_component_constraint(&door_it, 1, COMP_BLOCKING);
					if (!next_in_list_mask(&door_it)) {
						free_component(engine, itemaction_entity_id, COMP_INCONTAINER);
					}
					// Listiterator free
					free_entity_list_iterator(&door_it);
				}
			}
			// Listiterator free
			free_entity_list_iterator(&key_it);

		}
		else if (!player_input->actkey && system->prevAct == 1) {
			system->prevAct = 0;
		}
	}
	
}
