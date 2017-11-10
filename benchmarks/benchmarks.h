#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <stdio.h>

typedef enum Functions {
	HAS_COMPONENT = 0,
	GET_COMPONENT = 1,
	CREATE_COMPONENT = 2,
	FREE_COMPONENT = 3,
	GET_NEW_ENTITY_ID = 4
} Functions;

#include "../pi_escape/es/engine.h"

void register_has_comp(EntityId, ComponentId);
void register_get_comp(EntityId, ComponentId);
void register_create_comp(EntityId, ComponentId);
void register_free_comp(EntityId, ComponentId);
void register_get_ent_id();

void benchmark();
#endif