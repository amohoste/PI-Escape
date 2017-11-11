#define __STDC_FORMAT_MACROS

#include <inttypes.h>
#include <stdio.h>

#include "util/sleep.h"
#include "pi_escape/graphics/opengl_game_renderer.h"
#include "pi_escape/level/levelloader.h"
#include "pi_escape/es/game.h"
#ifdef RPI
#include "pi_escape/led/sense_led.h"
#endif // RPI


#include <SDL.h>

#undef main //Weird bug on windows where SDL overwrite main definition

#include <SDL_timer.h>

int main() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fatal("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    //init the graphics system
    Graphics *graphics = graphics_alloc(0, 0);

    //initialise context, engine and assemblage, and add systems
    Game *pi_escape_2 = game_alloc(graphics);

    //een level inladen kan je doen door gewoon op te  geven het hoeveelste level het is -> beginnend vanaf 1
    //vanaf level 7 worden de echte games geladen en niet de tutorials
    Level *level = load_level(1);
    game_load_level(pi_escape_2, level);

    pi_escape_2->engine.context.current_level = level;

    Uint32 start_time_ms = SDL_GetTicks();
    Uint32 last_print_time_ms = start_time_ms;
    long update_count = 0;
	
    while (!pi_escape_2->engine.context.is_exit_game) {
        Uint32 cur_time_ms = SDL_GetTicks();
        Uint32 diff_time_ms = cur_time_ms - last_print_time_ms;

        engine_update(&pi_escape_2->engine);
        update_count++;

        //kijken of er een nieuw level geladen moet worden
        if (pi_escape_2->engine.context.level_ended) {

            printf("has: %d\n", pi_escape_2->engine.context.has);
            printf("create: %d\n", pi_escape_2->engine.context.create);
            printf("get: %d\n", pi_escape_2->engine.context.get);
            printf("free: %d\n", pi_escape_2->engine.context.free);

            int new_level_nr = pi_escape_2->engine.context.current_level->nr + 1;
            if (new_level_nr > 10) {
                pi_escape_2->engine.context.is_exit_game = 1;
            } else {
                Level *next = load_level(new_level_nr);
                clear_level(pi_escape_2);
                game_load_level(pi_escape_2, next);
                pi_escape_2->engine.context.current_level = next;
                pi_escape_2->engine.context.level_ended = 0;
            }
        }

        //print performance statistics each second
        if (diff_time_ms > 1000) {
            float time_ms_per_update = (float) diff_time_ms / (float) update_count;
            float fps = 1.0f / time_ms_per_update * 1000.0f;
            pi_escape_2->engine.context.fps = fps;
            printf("This second: %f updates. Average time per update: %f ms.\n", fps, time_ms_per_update);
			printf("Temperature: %f celcius\n", pi_escape_2->engine.context.temperature);

            last_print_time_ms = cur_time_ms;
            update_count = 0;
        }
    }
#ifdef RPI
	clear_ledgrid();
#endif // RPI
    game_free(pi_escape_2);
    free(pi_escape_2);

    graphics_free(graphics);
    free(graphics);

    return 0;
}
