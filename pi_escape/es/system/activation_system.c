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
	
	// OR en AND entities zoeken
	EntityIterator logicit;
	search_entity_1(engine, COMP_CONNECTORLOGIC, &logicit);
	while (next_entity(&logicit)) {
		// Entity opvragen
		EntityId logicconnector_entity_id = logicit.entity_id;
		assert(logicconnector_entity_id != NO_ENTITY);


		ConnectorLogicComponent* con = get_component(engine, logicconnector_entity_id, COMP_CONNECTORLOGIC);

		if (con->type == AND_LOGIC) {

		}
		else if (con->type == OR_LOGIC) {

		}
	}

	// Connector entities zoeken
	
	
	
	//demo only, no use in real game
	EntityIterator it;
	search_entity_1(engine, COMP_ACTIVATABLE, &it);
	while (next_entity(&it)) {
		EntityId activatable_entity_id = it.entity_id;
		assert(activatable_entity_id != NO_ENTITY);
		ActivatableComponent* activatable = get_component(engine, activatable_entity_id, COMP_ACTIVATABLE);
		activatable->active = 1;
	}

}
