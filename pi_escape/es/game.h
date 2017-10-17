#ifndef GAME_H
#define GAME_H

#include "engine.h"

#include "../level/levelloader.h"

#include "context.h"
#include "assemblage.h"
#include "system/render_system.h"
#include "system/input_system.h"
#include "system/move_system.h"
#include "system/camera_system.h"
#include "system/lock_system.h"
#include "system/action_system.h"
#include "system/activation_system.h"
#include "system/container_system.h"
#include "system/endlevel_system.h"
#include "system/animation_system.h"
#include "system/process_sensor_system.h"
#ifdef RPI
#include "system/real_sensors_system.h"
#include "system/orientation_system.h"
#endif
#include "../graphics/opengl_game_renderer.h"

#define IS_START(x,y) l->spel[x][y] == 'S' || l->spel[x][y] == 's'
#define IS_EMPTY(x,y) l->spel[x][y] == ' '
#define IS_VERBINDING(x,y) l->spel[x][y] == '=' || l->spel[x][y] == '-' || l->spel[x][y] == '.'
#define IS_WALL(x,y) l->spel[x][y] == '*' || l->spel[x][y] == 'X' || l->spel[x][y] == 'x'
#define IS_DOOR(x,y) l->spel[x][y] == 'D' || l->spel[x][y] == 'd' || l->spel[x][y] == '#'
#define IS_AND(x,y) l->spel[x][y] == '&'
#define IS_OR(x,y) l->spel[x][y] == '|'
#define IS_EXIT(x,y) l->spel[x][y] == 'E' || l->spel[x][y] == 'e'
#define IS_KEY(x,y) l->spel[x][y] == 'a' || l->spel[x][y] == 'b'|| l->spel[x][y] == 'c'|| l->spel[x][y] == 'd'
#define IS_LOCK(x,y) l->spel[x][y] == 'A' || l->spel[x][y] == 'B'|| l->spel[x][y] == 'C'|| l->spel[x][y] == 'D'

typedef struct Game {
    Graphics* graphics;
    Engine engine;
} Game;

void game_init(Game*, Graphics*);
Game* game_alloc(Graphics*);
void game_free(Game*);

void game_load_level(Game*, Level*);

#endif //GAME_H
