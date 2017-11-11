#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <stdio.h>

typedef enum Functions {
	HAS_COMPONENT = 0,
	GET_COMPONENT = 1,
	CREATE_COMPONENT = 2,
	FREE_COMPONENT = 3,
	GET_NEW_ENTITY_ID = 4,
	NEW_LEVEL = 5
} Functions;

#include "../pi_escape/es/engine.h"

#define MAX_RECORD_SIZE 10

void register_has_comp(EntityId, ComponentId);
void register_get_comp(EntityId, ComponentId);
void register_create_comp(EntityId, ComponentId);
void register_free_comp(EntityId, ComponentId);
void register_get_ent_id();
void register_new_level();
void clear_file(char*);
#endif