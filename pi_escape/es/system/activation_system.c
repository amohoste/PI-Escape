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
	
	// Bij elke update
	// Over alle locks lopen
	EntityIterator lockit;
	search_entity_1(engine, COMP_LOCK, &lockit);
	while (next_entity(&lockit)) {
		// Entity opvragen
		EntityId lock_entity_id = lockit.entity_id;
		assert(lock_entity_id != NO_ENTITY);
		ActivatableComponent* activatable = get_component(engine, lock_entity_id, COMP_ACTIVATABLE);
		
		// Als slot gedeactiveerd
		if (activatable->active == 0) {
			EntityId curr = lock_entity_id;
			ConnectionsComponent *connection = get_component(engine, curr, COMP_CONNECTIONS);
			EntityId next = connection->downstream;

			// Zolang volgende component downstream heeft en deze geactiveerd is deze deactiveren
			while (connection->hasDownStream && ! has_component(engine, next, COMP_CONNECTORLOGIC)) {
				ActivatableComponent* activatable = get_component(engine, next, COMP_ACTIVATABLE);
				if (activatable->active == 1) {
					activatable->active = 0;
					curr = connection->downstream;
					connection = get_component(engine, curr, COMP_CONNECTIONS);
					next = connection->downstream;
				}
				else {
					break;
				}
			}
		}
	}

	// Over alle logica lopen
	EntityIterator logicit1;
	search_entity_1(engine, COMP_CONNECTORLOGIC, &logicit1);
	while (next_entity(&logicit1)) {
		// Entity opvragen
		EntityId logic_entity_id = logicit1.entity_id;
		assert(logic_entity_id != NO_ENTITY);
		ActivatableComponent* activatable = get_component(engine, logic_entity_id, COMP_ACTIVATABLE);

		// Als geactiveerd
		if (activatable->active == 1) {
			ConnectorLogicComponent *logic = get_component(engine, logic_entity_id, COMP_CONNECTORLOGIC);
			ConnectionsComponent *connection = get_component(engine, logic_entity_id, COMP_CONNECTIONS);
			// Kijken of een uit is en indien dit zo is and uit zetten
			if (logic->type == AND_LOGIC) {
				if (connection->hasUpStream1) {
					ActivatableComponent* active = get_component(engine, connection->upstream[0], COMP_ACTIVATABLE);
					activatable->active *= active->active;
				}
				if (connection->hasUpStream2) {
					ActivatableComponent* active = get_component(engine, connection->upstream[1], COMP_ACTIVATABLE);
					activatable->active *= active->active;
				}
				if (connection->hasUpStream3) {
					ActivatableComponent* active = get_component(engine, connection->upstream[2], COMP_ACTIVATABLE);
					activatable->active *= active->active;
				}

			}
			else if (logic->type == OR_LOGIC) {
				int status = 0;
				if (connection->hasUpStream1) {
					ActivatableComponent* active = get_component(engine, connection->upstream[0], COMP_ACTIVATABLE);
					status += active->active;
				}
				if (connection->hasUpStream2) {
					ActivatableComponent* active = get_component(engine, connection->upstream[1], COMP_ACTIVATABLE);
					status += active->active;
				}
				if (connection->hasUpStream3) {
					ActivatableComponent* active = get_component(engine, connection->upstream[2], COMP_ACTIVATABLE);
					status += active->active;
				}
				if (status == 0) {
					activatable->active = 0;
				}
			}

			// Indien logica gedeactiveerd alle volgende deactiveren tot volgende null / logica is
			// Als logica gedeactiveerd
			if (activatable->active == 0) {
				EntityId curr = logic_entity_id;
				ConnectionsComponent *connection = get_component(engine, curr, COMP_CONNECTIONS);
				EntityId next = connection->downstream;

				// Zolang volgende component downstream heeft en deze geactiveerd is deze deactiveren
				while (connection->hasDownStream && !has_component(engine, next, COMP_CONNECTORLOGIC)) {
					ActivatableComponent* activatable = get_component(engine, next, COMP_ACTIVATABLE);
					if (activatable->active == 1) {
						activatable->active = 0;
						curr = connection->downstream;
						connection = get_component(engine, curr, COMP_CONNECTIONS);
						next = connection->downstream;
					}
					else {
						break;
					}
				}
			}
		}
	}
	


	// Om de x aantal seconden -> later aanpassen
	// Over alle logica lopen
	int changed = 0;
	EntityIterator logicit2;
	search_entity_1(engine, COMP_CONNECTORLOGIC, &logicit2);
	while (next_entity(&logicit2)) {
		// Entity opvragen
		EntityId logic_entity_id = logicit2.entity_id;
		assert(logic_entity_id != NO_ENTITY);
		ActivatableComponent* activatable = get_component(engine, logic_entity_id, COMP_ACTIVATABLE);

		// Als gedeactiveerd
		if (activatable->active == 0) {
			ConnectorLogicComponent *logic = get_component(engine, logic_entity_id, COMP_CONNECTORLOGIC);
			ConnectionsComponent *connection = get_component(engine, logic_entity_id, COMP_CONNECTIONS);
			// Kijken of een uit is en indien dit zo is and uit zetten
			if (logic->type == AND_LOGIC) {
				int status = 1;
				if (connection->hasUpStream1) {
					ActivatableComponent* active = get_component(engine, connection->upstream[0], COMP_ACTIVATABLE);
					 status *= active->active;
				}
				if (connection->hasUpStream2) {
					ActivatableComponent* active = get_component(engine, connection->upstream[1], COMP_ACTIVATABLE);
					status *= active->active;
				}
				if (connection->hasUpStream3) {
					ActivatableComponent* active = get_component(engine, connection->upstream[2], COMP_ACTIVATABLE);
					status *= active->active;
				}
				activatable->active = status;
			}
			else if (logic->type == OR_LOGIC) {
				int status = 0;
				if (connection->hasUpStream1) {
					ActivatableComponent* active = get_component(engine, connection->upstream[0], COMP_ACTIVATABLE);
					status += active->active;
				}
				if (connection->hasUpStream2) {
					ActivatableComponent* active = get_component(engine, connection->upstream[1], COMP_ACTIVATABLE);
					status += active->active;
				}
				if (connection->hasUpStream3) {
					ActivatableComponent* active = get_component(engine, connection->upstream[2], COMP_ACTIVATABLE);
					status += active->active;
				}
				if (status > 0) {
					activatable->active = 1;
				}
				else {
					activatable->active = 0;
				}
			}

			// Indien logica geactiveerd alle volgende activeren tot volgende null / logica is
			// Als logica gedeactiveerd
			if (activatable->active == 1) {
				changed = 1;
			}
		}
	}
	
	// Indien logica niet aangepast over alle andere lopen
	if (!changed) {
		EntityIterator it;
		search_entity_2(engine, COMP_ACTIVATABLE, COMP_CONNECTIONS, &it);
		while (next_entity(&it)) {
			EntityId entity_id = it.entity_id;
			assert(entity_id != NO_ENTITY);
			ActivatableComponent* activatable = get_component(engine, entity_id, COMP_ACTIVATABLE);
			if (activatable->active == 1) {
				ConnectionsComponent *connection = get_component(engine, entity_id, COMP_CONNECTIONS);
				if (connection->hasDownStream) {
					EntityId next_id = connection->downstream;
					if (!has_component(engine, next_id, COMP_CONNECTORLOGIC)) {
						ActivatableComponent* next_activatable = get_component(engine, next_id, COMP_ACTIVATABLE);
						if (next_activatable->active == 0) {
							next_activatable->active = 1;
							break;
						}
					}
				}
			}
		}
	}

	
	// TODO: deuren
	//demo only, no use in real game
	/*
	EntityIterator it;
	search_entity_1(engine, COMP_LOCK, &it);
	while (next_entity(&it)) {
		EntityId activatable_entity_id = it.entity_id;
		assert(activatable_entity_id != NO_ENTITY);
		ActivatableComponent* activatable = get_component(engine, activatable_entity_id, COMP_ACTIVATABLE);
		activatable->active = 1;
	}
	*/

}
