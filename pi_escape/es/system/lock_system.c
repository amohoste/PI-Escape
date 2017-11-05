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

		// Over alle sleutels lopen en als locatie gelijk is lock activeren
		EntityIterator key_it;
		search_entity_1(engine, COMP_ITEM, &key_it);
		while (next_entity(&key_it)) {
			EntityId key_entity_id = key_it.entity_id;
			assert(key_entity_id != NO_ENTITY);

			GridLocationComponent* keygrid = get_component(engine, key_entity_id, COMP_GRIDLOCATION);
			int x1 = keygrid->pos[0];
			int y1 = keygrid->pos[1];

			ItemComponent *item = get_component(engine, key_entity_id, COMP_ITEM);
			ItemColor color = item->color;

			if ((x == x1 && y == y1 && (requiredKeyColor == color || color == O || requiredKeyColor == O))) {
				active = 1;
			}
		}
		ActivatableComponent* activatable = get_component(engine, lock_entity_id, COMP_ACTIVATABLE);
		activatable->active = active;
	}

}
