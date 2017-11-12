#include "game.h"

#include <stdlib.h>

void game_init(Game *game, Graphics *graphics, int benchmarking) {
    game->graphics = graphics;
    engine_init(&game->engine, graphics, benchmarking);
}

Game *game_alloc(Graphics *graphics, int benchmarking) {
    Game *res = malloc(sizeof(Game));
    game_init(res, graphics, benchmarking);
    return res;
}

void game_free(Game *game) {
    engine_free(&game->engine);
    //don't free graphics
}

void game_load_level(Game *g, Level *l) {
    Engine *engine = &g->engine;
    create_level_entities(l, engine);
}

void clear_level(Game *g) {
    es_memory_manager_free(&g->engine.es_memory);
	#ifdef BENCHMARK
		register_new_level();
	#endif // BENCHMARK
    es_memory_manager_init(&g->engine.es_memory);
}