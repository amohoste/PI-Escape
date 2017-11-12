#include "lock_system.h"


#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

LockSystem* system_lock_alloc() {
    LockSystem* res = calloc(1, sizeof(LockSystem));
    system_lock_init(res);
    return res;
}

void system_lock_init(LockSystem* system) {
    //TODO
}


void system_lock_free(LockSystem* system) {
    //TODO
}


void system_lock_update(LockSystem* system, Engine* engine) {
    // Alle sloten opzoeken
	EntityIterator lock_it;
	search_entity_1(engine, COMP_LOCK, &lock_it);
	while (next_entity(&lock_it)) {
		int active = 0;
		EntityId lock_entity_id = lock_it.entity_id;
		assert(lock_entity_id != NO_ENTITY);
		GridLocationComponent* lockgrid = get_component(engine, lock_entity_id, COMP_GRIDLOCATION);
		int x = lockgrid->pos[0];
		int y = lockgrid->pos[1];
		LockComponent *lock = get_component(engine, lock_entity_id, COMP_LOCK);
		ItemColor requiredKeyColor = lock->requiredKeyColor;

		EntityListIterator key_it;
		start_search_in_list(x, y, engine, &key_it);
		add_component_constraint(&key_it, 1, COMP_ITEM);

		while (next_in_list_mask(&key_it)) {
			EntityId key_entity_id = key_it.entity_id;
			assert(key_entity_id != NO_ENTITY);

			ItemComponent *item = get_component(engine, key_entity_id, COMP_ITEM);
			ItemColor color = item->color;

			if (requiredKeyColor == color || color == O || requiredKeyColor == O) {
				if (!has_component(engine, key_entity_id, COMP_INCONTAINER)) {
					active = 1;
				}

			}
		}

		ActivatableComponent* activatable = get_component(engine, lock_entity_id, COMP_ACTIVATABLE);
		activatable->active = active;
	}

}
