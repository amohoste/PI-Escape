#include "benchmarks.h"

void register_has_comp(EntityId entity_id, ComponentId component_id) {
	FILE *file = fopen("benchmarks.txt", "a");
	fprintf(file, "%i %i %i\n", HAS_COMPONENT, entity_id, component_id);
	fclose(file);
}

void register_get_comp(EntityId entity_id, ComponentId component_id) {
	FILE *file = fopen("benchmarks.txt", "a");
	fprintf(file, "%i %i %i\n", GET_COMPONENT, entity_id, component_id);
	fclose(file);
}

void register_create_comp(EntityId entity_id, ComponentId component_id) {
	FILE *file = fopen("benchmarks.txt", "a");
	fprintf(file, "%i %i %i\n", CREATE_COMPONENT,  entity_id, component_id);
	fclose(file);
}

void register_free_comp(EntityId entity_id, ComponentId component_id) {
	FILE *file = fopen("benchmarks.txt", "a");
	fprintf(file, "%i %i %i\n", FREE_COMPONENT, entity_id, component_id);
	fclose(file);
}

void register_get_ent_id() {
	FILE *file = fopen("benchmarks.txt", "a");
	fprintf(file, "%i\n", GET_NEW_ENTITY_ID);
	fclose(file);
}

void clear_file(char* dest) {
	FILE *file = fopen(dest, "w");
	fprintf(file, "");
	fclose(file);
}