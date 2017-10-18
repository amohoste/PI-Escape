#include "game.h"

#include <stdlib.h>

void game_init(Game *game, Graphics *graphics) {
    game->graphics = graphics;
    engine_init(&game->engine, graphics);
}

Game *game_alloc(Graphics *graphics) {
    Game *res = malloc(sizeof(Game));
    game_init(res, graphics);
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
