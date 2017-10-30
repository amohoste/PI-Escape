#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "assemblage.h"


void create_level_entities(Level *l, Engine *engine) {
    EntityId **entityList;
    entityList = (EntityId **) calloc((size_t) l->height, sizeof(EntityId *));
    for (int i = 0; i < l->height; i++) {
        entityList[i] = (EntityId *) calloc((size_t) l->width, sizeof(EntityId));
    }
    for (int x = 0; x < l->height; x++) {
        for (int y = 0; y < l->width; y++) {
            int has_door = IS_DOOR(x, y);
            int has_floor = !has_door;
            int has_ceil = !has_floor && !has_door;
            int has_key = IS_KEY(x, y);
            int has_player = IS_START(x, y);
            int has_lock = IS_LOCK(x, y);
            int has_wall = IS_WALL(x, y);
            int has_or = IS_OR(x, y);
            int has_and = IS_AND(x, y);
            int is_verbinding = IS_VERBINDING(x, y);
            int is_exit = IS_EXIT(x, y);

            int walls[4];
            walls[S] = y == 0 || has_wall;
            walls[N] = y == l->width - 1 || has_wall;
            walls[E] = x == l->height - 1 || has_wall;
            walls[W] = x == 0 || has_wall;

            if (has_player) {
                entityList[x][y] = create_player_entity(engine, x, y);
            }

            if (has_door) {
                entityList[x][y] = create_door_entity(engine, l, x, y);
            }
            if (has_lock) {
                entityList[x][y] = create_lock_entity(engine, x, y, l->spel[x][y]);
            }
            if (has_key) {
                entityList[x][y] = create_key_entity(engine, x, y, l->spel[x][y]);
            }

            if (has_or) {
                entityList[x][y] = create_or_entity(engine, x, y);
            }

            if (has_and) {
                entityList[x][y] = create_and_entity(engine, x, y);
            }

            if (is_verbinding) {
                entityList[x][y] = create_verbinding_entity(engine, l, x, y);
            }

            if (is_exit) {
                entityList[x][y] = create_exit_entity(engine, x, y);
            }

            /* walls moeten altijd gemaakt worden voor de vloer enzo */
            EntityId wall = create_wall_entity(engine, x, y, has_floor, has_ceil, has_wall, walls);

        }
    }
}

EntityId create_exit_entity(Engine *engine, int x, int y) {
    EntityId exit_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridLoc = create_component(engine, exit_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridLoc->pos, x, y);

    ArtComponent *art = create_component(engine, exit_entity_id, COMP_ART);
    art->type = ART_END;

    ExitComponent *exit = create_component(engine, exit_entity_id, COMP_EXIT);
}

EntityId create_verbinding_entity(Engine *engine, Level *l, int x, int y) {
    EntityId verb_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridLoc = create_component(engine, verb_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridLoc->pos, x, y);

    ArtComponent *art = create_component(engine, verb_entity_id, COMP_ART);
    art->type = ART_CONNECTOR;

    DirectionComponent *dir = create_component(engine, verb_entity_id, COMP_DIRECTION);
    //kijken of het vakje erboven of eronder aantoont hoe er moet worden bewogen
    if (x >= 1 && (IS_VERBINDING(x - 1, y) || IS_AND(x - 1, y) || IS_DOOR(x - 1, y) || IS_OR(x - 1, y))) {
        dir->dir = E;
    } else {
        dir->dir = S;
    }

    ActivatableComponent *act = create_component(engine, verb_entity_id, COMP_ACTIVATABLE);
    act->active = 0;

    return verb_entity_id;
}

EntityId create_and_entity(Engine *engine, int x, int y) {
    EntityId or_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, or_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, or_entity_id, COMP_ART);
    art->type = ART_CONNECTOR_AND;

    ConnectorLogicComponent *con = create_component(engine, or_entity_id, COMP_CONNECTORLOGIC);

    ActivatableComponent *act = create_component(engine, or_entity_id, COMP_ACTIVATABLE);

    return or_entity_id;
}

EntityId create_or_entity(Engine *engine, int x, int y) {
    EntityId or_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, or_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, or_entity_id, COMP_ART);
    art->type = ART_CONNECTOR_OR;

    ConnectorLogicComponent *con = create_component(engine, or_entity_id, COMP_CONNECTORLOGIC);

    ActivatableComponent *act = create_component(engine, or_entity_id, COMP_ACTIVATABLE);

    return or_entity_id;
}

EntityId create_player_entity(Engine *engine, int x, int y) {
    EntityId player_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, player_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, player_entity_id, COMP_ART);
    art->type = ART_PLAYER;

    create_component(engine, player_entity_id, COMP_INPUTRECEIVER);

    CameraLookAtComponent *cameralookat = create_component(engine, player_entity_id, COMP_CAMERA_LOOK_AT);
    glmc_vec3_set(cameralookat->pos, x * 1.0f, y * 1.0f, 0.0f);

    CameraLookFromComponent *cameralookfrom = create_component(engine, player_entity_id,
                                                               COMP_CAMERA_LOOK_FROM);
    cameralookfrom->distance = 15.0f;
    cameralookfrom->XYdegees = 0.0f;
    cameralookfrom->Zdegrees = 25.0f;
    glmc_vec3_set(cameralookfrom->pos, 4.0f, -4.0f, 4.0f); //this normally gets overridden by camera system

	MoveActionComponent *move = create_component(engine, player_entity_id, COMP_MOVE_ACTION);

	ItemActionComponent *itemaction = create_component(engine, player_entity_id, COMP_ITEMACTION);

    return player_entity_id;
}

EntityId create_door_entity(Engine *engine, Level *l, int x, int y) {
    EntityId door_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, door_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ActivatableComponent *activatable = create_component(engine, door_entity_id, COMP_ACTIVATABLE);
    activatable->active = 0;

    DirectionComponent *directioncomponent = create_component(engine, door_entity_id, COMP_DIRECTION);
    if ((x > 1 && IS_WALL(x - 1, y)) || (x < l->width - 1 && IS_WALL(x + 1, y))) {
        directioncomponent->dir = E;
    } else {
        directioncomponent->dir = N;
    }

    ArtComponent *art = create_component(engine, door_entity_id, COMP_ART);
    art->type = ART_DOOR;

    return door_entity_id;
}

EntityId create_lock_entity(Engine *engine, int x, int y, char color) {
    EntityId lock_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, lock_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ActivatableComponent *activatable = create_component(engine, lock_entity_id, COMP_ACTIVATABLE);
    activatable->active = 0;

    ArtComponent *art = create_component(engine, lock_entity_id, COMP_ART);
    art->type = ART_LOCK;

    LockComponent *lock = create_component(engine, lock_entity_id, COMP_LOCK);
    switch (color) {
        case 'A':
            lock->requiredKeyColor = A;
            break;
        case 'B':
            lock->requiredKeyColor = B;
            break;
        case 'C' :
            lock->requiredKeyColor = C;
            break;
        case 'O':
            lock->requiredKeyColor = O;
            break;
        default:
            break;
    }

    return lock_entity_id;
}

EntityId create_key_entity(Engine *engine, int x, int y, char color) {
    EntityId key_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, key_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ItemComponent *item = create_component(engine, key_entity_id, COMP_ITEM);
    switch (color) {
        case 'a':
            item->
                    color = A;
            break;
        case 'b':
            item->
                    color = B;
            break;
        case 'c' :
            item->
                    color = C;
            break;
        case 'o':
            item->
                    color = O;
            break;
        default:
            break;
    }

    ArtComponent *art = create_component(engine, key_entity_id, COMP_ART);
    art->type = ART_KEY;

    return key_entity_id;
}

EntityId create_wall_entity(Engine *engine, int x, int y, int has_floor, int has_ceil, int has_wall, int walls[4]) {

    EntityId wall_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, wall_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, wall_entity_id, COMP_ART);
    art->type = ART_WALL;

    WallArtComponent *wall = create_component(engine, wall_entity_id, COMP_WALLART);

    wall->has_floor = has_floor;
    wall->has_ceil = has_ceil || has_wall;
    wall->has_wall[S] = walls[S];
    wall->has_wall[N] = walls[N];
    wall->has_wall[E] = walls[E];
    wall->has_wall[W] = walls[W];

    return wall_entity_id;

}
