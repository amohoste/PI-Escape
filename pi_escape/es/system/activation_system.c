#include "activation_system.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

ActivationSystem* system_activation_alloc() {
    ActivationSystem* res = calloc(1, sizeof(ActivationSystem));
    system_activation_init(res);
    return res;
}

void system_activation_init(ActivationSystem* system) {
    //TODO
}


void system_activation_free(ActivationSystem* system) {
    //TODO
}


void system_activation_update(ActivationSystem* system, Engine* engine) {
	//demo only, no use in real game
	EntityIterator it;
	search_entity_1(engine, COMP_ACTIVATABLE, &it);
	while (next_entity(&it)) {
		EntityId drawable_entity_id = it.entity_id;
		assert(drawable_entity_id != NO_ENTITY);
		ActivatableComponent* activatable = get_component(engine, drawable_entity_id, COMP_ACTIVATABLE);
		activatable->active = !engine->context.demo;
	}

}
