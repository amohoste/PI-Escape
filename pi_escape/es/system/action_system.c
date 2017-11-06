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

	// Locatie speler opvragen
	EntityIterator player_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_INPUTRECEIVER, &player_it);
	next_entity(&player_it);
	EntityId player_entity_id = player_it.entity_id;
	assert(player_entity_id != NO_ENTITY);
	ItemActionComponent* player_itemact = get_component(engine, player_entity_id, COMP_ITEMACTION);
	
	// Als player act
	if (player_itemact->act) {
		GridLocationComponent* player_grid_comp = get_component(engine, player_entity_id, COMP_GRIDLOCATION);
		int player_x = player_grid_comp->pos[0];
		int player_y = player_grid_comp->pos[1];

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

			}

			// Neerleggen als zelfde locatie slot met zelfde kleur heeft
			ItemComponent *item = get_component(engine, itemaction_entity_id, COMP_ITEM);
			ItemColor key_color = item->color;

			EntityIterator lock_it;
			search_entity_1(engine, COMP_LOCK, &lock_it);
			while (next_entity(&lock_it)) {
				EntityId lock_entity_id = lock_it.entity_id;
				assert(lock_entity_id != NO_ENTITY);
				GridLocationComponent* lockgrid = get_component(engine, lock_entity_id, COMP_GRIDLOCATION);
				int lock_x = lockgrid->pos[0];
				int lock_y = lockgrid->pos[1];
				LockComponent *lock = get_component(engine, lock_entity_id, COMP_LOCK);
				ItemColor requiredKeyColor = lock->requiredKeyColor;
				// Todo: maybe general function to check wether key is equal to lock?
				if ((requiredKeyColor == key_color || key_color == O || requiredKeyColor == O) && key_x == lock_x && key_y == lock_y) {
					if (has_component(engine, itemaction_entity_id, COMP_INCONTAINER)) {
						free_component(engine, itemaction_entity_id, COMP_INCONTAINER);
					}
				}

			}
		}
	}
	
}
