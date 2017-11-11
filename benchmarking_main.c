#include <stdio.h>

#include "benchmarks/benchmarks.h"
#include "pi_escape/graphics/opengl_game_renderer.h"
#include "pi_escape/level/levelloader.h"
#include "pi_escape/es/game.h"

#undef main //Weird bug on windows where SDL overwrite main definition

int main(int argc, char **argv){
    // Get specified file
	printf("Benchmark simulation started ...\n\n");
	//if(argc > 0) return -1;
	//char * benchmark_file = argv[0];

	// Start simulation

	Engine* engine = calloc(1, sizeof(Engine));
	es_memory_manager_init(&engine->es_memory);

	// Go over all records in the file
	FILE * file = fopen("benchmarks.txt", "r");
	char line[MAX_RECORD_SIZE];

	int count = 0;

	while (!feof(file)) {
		count++;
		int a = -1;
		int b = -1;
		int c = -1;

		// Read line
		fgets(line, MAX_RECORD_SIZE, file);
		sscanf(line, "%i %i %i", &a, &b, &c);
		Functions function = (Functions)a;

		// perform logged function
		switch (function)
		{
			case HAS_COMPONENT: {
				has_component(engine, b, c);
				break;
			}
			case GET_COMPONENT: {
				get_component(engine, b, c);
				break;
			}
			case CREATE_COMPONENT: {
				create_component(engine, b, c);
				break;
			}
			case FREE_COMPONENT: {
				free_component(engine, b, c);
				break;
			}
			case GET_NEW_ENTITY_ID: {
				get_new_entity_id(engine);
				break;
			}
			case NEW_LEVEL: {
				es_memory_manager_init(&engine->es_memory);
				break;
			}
			default: {
				break;
			}
		}
	}
	printf("\nsimulation finished. %i calls.\n", count);
	printf("Press any key to continue...");
	getchar();

    return 0;
}
