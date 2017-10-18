#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "assemblage.h"

void create_level_entities(Level *l, Engine *engine) {
    for (int x = 0; x < l->height; x++) {
        for (int y = 0; y < l->width; y++) {
            int has_door = IS_DOOR(x, y);
            int has_floor = !has_door;
            int has_ceil = !has_floor && !has_door;
            int has_key = IS_KEY(x, y);
            int has_player = IS_START(x, y);
            int has_lock = IS_LOCK(x, y);
            int has_wall = IS_WALL(x, y);

            if (has_player) {
                //todo waarom returntype?
                EntityId player = create_player_entity(engine, x, y);
            }

            if (has_door) {
                EntityId door = create_door_entity(engine, x, y);
            }
            if (has_lock) {
                EntityId lock = create_lock_entity(engine, x, y, l->spel[x][y]);
            }
            if (has_key) {
                EntityId key = create_key_entity(engine, x, y, l->spel[x][y]);
            }

            /* walls moeten altijd gemaakt worden voor de vloer enzo */
            EntityId wall = create_wall_entity(engine, x, y, has_floor, has_ceil);

        }
    }
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

    return player_entity_id;
}

EntityId create_door_entity(Engine *engine, int x, int y) {
    EntityId door_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, door_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ActivatableComponent *activatable = create_component(engine, door_entity_id, COMP_ACTIVATABLE);
    activatable->active = 0;

    DirectionComponent *directioncomponent = create_component(engine, door_entity_id, COMP_DIRECTION);
    directioncomponent->dir = N;

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

    //TODO beter dan switchopdrachten?
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

EntityId create_wall_entity(Engine *engine, int x, int y, int has_floor, int has_ceil) {

    EntityId wall_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, wall_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);


    WallArtComponent *wall = create_component(engine, wall_entity_id, COMP_WALLART);

    wall->has_floor = has_floor;
    wall->has_ceil = has_ceil;
//    wall->has_wall[S] = y == 0 || has_wall;
//    wall->has_wall[N] = y == l->width - 1 || has_wall;
//    wall->has_wall[E] = x == l->height - 1 || has_wall;
//    wall->has_wall[W] = x == 0 || has_wall;

    return wall_entity_id;

}
