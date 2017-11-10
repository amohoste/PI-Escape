#include <stdio.h>

#include "benchmarks/benchmarks.h"
#include "pi_escape/graphics/opengl_game_renderer.h"
#include "pi_escape/level/levelloader.h"
#include "pi_escape/es/game.h"

#undef main //Weird bug on windows where SDL overwrite main definition

#include <SDL_timer.h>

int main(int argc, char **argv){
    // Get specified file
	printf("Benchmark simulation started ...\n\n");
	//if(argc > 0) return -1;
	//char * benchmark_file = argv[0];

	// Start simulation

	Engine* engine = calloc(1, sizeof(Engine));

	// Go over all records in the file
	FILE * file = fopen("benchmarks.txt", "r");
	char line[MAX_RECORD_SIZE];

	Uint32 start_time_ms = SDL_GetTicks();
	Uint32 last_print_time_ms = start_time_ms;
	long update_count = 0;

	while (!feof(file)) {
		int a = -1;
		int b = -1;
		int c = -1;
		fscanf(file, "%i %i %i", &a, &b, &c);
		Functions function = (Functions)a;

		Uint32 cur_time_ms = SDL_GetTicks();
		Uint32 diff_time_ms = cur_time_ms - last_print_time_ms;
		update_count++;

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
				has_component(engine, b, c);
				break;
			}
			default: {
				get_new_entity_id(engine);
				break;
			}
		}

		//print performance statistics each second
		if (diff_time_ms > 1000) {
			float time_ms_per_update = (float)diff_time_ms / (float)update_count;
			float fps = 1.0f / time_ms_per_update * 1000.0f;
			engine->context.fps = fps;
			printf("This second: %f updates. Average time per update: %f ms.\n", fps, time_ms_per_update);
			last_print_time_ms = cur_time_ms;
			update_count = 0;
		}
	}

    return 0;
}
