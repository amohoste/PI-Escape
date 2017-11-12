/***************************************************************
- Assemblage (assembly) -
Biedt functies om typische soorten entities en al hun 
components aan te maken.
****************************************************************/

#ifndef ASSEMBLAGE_H
#define ASSEMBLAGE_H

#include <glmc.h>
#include "../level/levelloader.h"
#include "game_util.h"
#include "engine.h"

#define IS_START(x, y) l->spel[x][y] == 'S' || l->spel[x][y] == 's'
#define IS_EMPTY(x, y) l->spel[x][y] == ' '
#define IS_VERBINDING(x, y) l->spel[x][y] == '=' || l->spel[x][y] == '-' || l->spel[x][y] == '.'
#define IS_WALL(x, y) l->spel[x][y] == '*' || l->spel[x][y] == 'X' || l->spel[x][y] == 'x'
#define IS_DOOR(x, y) l->spel[x][y] == 'D' || l->spel[x][y] == 'd' || l->spel[x][y] == '#'
#define IS_AND(x, y) l->spel[x][y] == '&'
#define IS_OR(x, y) l->spel[x][y] == '|'
#define IS_EXIT(x, y) l->spel[x][y] == 'E' || l->spel[x][y] == 'e'
#define IS_KEY(x, y) l->spel[x][y] == 'a' || l->spel[x][y] == 'b'|| l->spel[x][y] == 'c'|| l->spel[x][y] == 'o'
#define IS_LOCK(x, y) l->spel[x][y] == 'A' || l->spel[x][y] == 'B'|| l->spel[x][y] == 'C'|| l->spel[x][y] == 'O'

#define IS_VERBINDING_DIRECTION(x, y) IS_VERBINDING(x,y) || IS_DOOR(x,y) || IS_LOCK(x,y) || IS_AND(x,y) || IS_OR(x,y)

//TODO
//example: EntityId createKey(Engine* engine, t_ivec2 tvec2, ItemColor color);

EntityId create_player_entity(Engine *engine, int x, int y);

EntityId create_door_entity(Engine *engine, Level *l, int x, int y);

EntityId create_lock_entity(Engine *engine, int x, int y, char color);

EntityId create_key_entity(Engine *engine, int x, int y, char color);

EntityId
create_wall_entity(Engine *engine, Level *l, int x, int y, int has_floor, int has_door, int has_wall, int walls[4]);

EntityId create_verbinding_entity(Engine *engine, Level *l, int x, int y, Direction direction);

EntityId create_or_entity(Engine *engine, int x, int y);

EntityId create_and_entity(Engine *engine, int x, int y);

EntityId create_exit_entity(Engine *engine, int x, int y);

void create_wall(Engine *engine, int x, int y, Direction direction);

void create_level_entities(Level* l, Engine * engine);

// Functies om de connectioncomponenten te initialiseren
void create_all_verbinding_entities(Level *l, Engine *engine, EntityId **entityList);
void create_connections(Level *l, Engine *engine, int x, int y, EntityId **entityList, int logic);
EntityId create_first_verbinding_entity_logic(Engine *engine, Level *l, ConnectionsComponent *comp, int x, int y);
EntityId create_first_verbinding_entity_lock(Engine *engine, Level *l, int x, int y);
EntityId create_verbinding_entity_1(Engine *engine, Level *l, int x, int y, Direction lastdir);
EntityId create_verbinding_entity_2(Engine *engine, Level *l, int x, int y, Direction lastdir);
void nextLocation_dir(int *curx, int *cury, int *prevx, int *prevy, Direction dir);
void nextLocation(int *curx, int *cury, int *prevx, int *prevy, Level *l);
int dir_in(Direction dir, DirectionComponent* locations[3], int n);
void addUpStream(ConnectionsComponent* conn, EntityId id);
void addDownStream(ConnectionsComponent* conn, EntityId id);

#endif