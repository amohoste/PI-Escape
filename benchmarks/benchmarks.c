#include "benchmarks.h"

void register_has_comp(EntityId entity_id, ComponentId component_id) {
	FILE *file = fopen("benchmarks.txt", "a");
	fprintf(file, "%i %i\n", HAS_COMPONENT, entity_id, component_id);
	fflush(file);
	fclose(file);
}

void register_get_comp(EntityId entity_id, ComponentId component_id) {
	FILE *file = fopen("test.txt", "a");
	fprintf(file, "%i %i\n", GET_COMPONENT, entity_id, component_id);
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

void benchmark() {
	FILE * file = fopen("benchmarks.txt", "r");
	char line[10];

	while (!feof(file)) {
		int a = -1;
		int b = -1;
		int c = -1;
		fscanf(file, "%i %i %i", &a, &b, &c);
		Functions function = (Functions) a;
		switch (function)
		{
			case HAS_COMPONENT: {
				break;
			}
			case GET_COMPONENT: {
				break;
			}
			case CREATE_COMPONENT: {
				break;
			}
			case FREE_COMPONENT: {
				break;
			}
			case GET_NEW_ENTITY_ID: {
				break;
			}
			default: {
				break;
			}
		}
	}
}