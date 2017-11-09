#ifndef BENCHMARKS_H
#define BENCHMARKS_H

typedef enum Functions {
	HAS_COMPONENT,
	GET_COMPONENT,
	CREATE_COMPONENT,
	FREE_COMPONENT,
	GET_NEW_ENTITY_ID
} Functions;

void register_get(int param);
void benchmark();
#endif