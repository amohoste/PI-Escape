#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>

#include "util/sleep.h"
#include "pi_escape/graphics/opengl_game_renderer.h"
#include "pi_escape/level/levelloader.h"
#include "pi_escape/es/game.h"

#include <SDL.h>
#undef main //Weird bug on windows where SDL overwrite main definition
#include <SDL_timer.h>


int main() {
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        fatal("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    struct LevelLoader* level_loader = levelloader_alloc();
    level_loader->file = "pi_escape/level/level_files/game2.lvl";

    //init the graphics system
    Graphics* graphics = graphics_alloc(0, 0);

    //initialise context, engine and assemblage, and add systems
    Game* pi_escape_2 = game_alloc(graphics);

    //TODO: don't use this
//    create_demo_entities(&pi_escape_2->engine);

    //TODO: use the 2 lines below instead of using create_demo_entities
     Level* level = levelloader_load_level(level_loader, 0);
     game_load_level(pi_escape_2, level);

    //TODO: support playing all levels in sequence

    Uint32 start_time_ms = SDL_GetTicks();
    Uint32 last_print_time_ms = start_time_ms;
    long update_count = 0;

    while (!pi_escape_2->engine.context.is_exit_game) {
        Uint32 cur_time_ms = SDL_GetTicks();
        Uint32 diff_time_ms = cur_time_ms - last_print_time_ms;

        engine_update(&pi_escape_2->engine);
        update_count++;

        //print performance statistics each second
        if (diff_time_ms > 1000) {
            float time_ms_per_update = (float)diff_time_ms / (float)update_count;
            float fps = 1.0f / time_ms_per_update * 1000.0f;
            printf("This second: %f updates. Average time per update: %f ms.\n", fps, time_ms_per_update);

            last_print_time_ms = cur_time_ms;
            update_count = 0;
        }
    }

    game_free(pi_escape_2);
    free(pi_escape_2);

    graphics_free(graphics);
    free(graphics);

    levelloader_free(level_loader);
    free(level_loader);

    return 0;
}
