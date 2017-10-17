#include "game.h"

#include <stdlib.h>

void game_init(Game* game, Graphics* graphics) {
    game->graphics = graphics;
    engine_init(&game->engine, graphics);
}

Game* game_alloc(Graphics* graphics) {
    Game* res = malloc(sizeof(Game));
    game_init(res, graphics);
    return res;
}

void game_free(Game* game) {
    engine_free(&game->engine);
    //don't free graphics
}

void game_load_level(Game* g, Level* l) {
    //TODO: use assembly to create all entities needed for the level
    Engine * engine = &g->engine;
    //As a demo, this creates a few example entities. This should be completely replaced by the level_loader and assemblage in the real game
    for (int x = 0; x < l->rij; x++) {
        for (int y = 0; y < l->kol; y++) {
            int has_door = x == 2 && y == 2;
            int has_floor = x != 2 && !has_door;
            int has_ceil = !has_floor && !has_door;
            int has_key = x == 1 && y == 1;
            int has_player = x == 3 && y == 3;
            int has_lock = x == 0 && y == 0;

            EntityId entity_id = get_new_entity_id(engine);

            GridLocationComponent* gridloc = create_component(engine, entity_id, COMP_GRIDLOCATION);
            glmc_ivec2_set(gridloc->pos, x, y);

            ArtComponent* art = create_component(engine, entity_id, COMP_ART);
            art->type = ART_WALL;

            WallArtComponent* wall_info = create_component(engine, entity_id, COMP_WALLART);
            wall_info->has_ceil = has_ceil;
            wall_info->has_floor = has_floor;
            wall_info->has_wall[N] = has_door || y == 4 ;
            wall_info->has_wall[S] = has_door || y == 0 ;
            wall_info->has_wall[W] = x == 0 || (x == 3 && y != 2);
            wall_info->has_wall[E] = x == 4 || (x == 1 && y != 2);

            if (has_key) {
                EntityId key_entity_id = get_new_entity_id(engine);

                GridLocationComponent* gridloc = create_component(engine, key_entity_id, COMP_GRIDLOCATION);
                glmc_ivec2_set(gridloc->pos, x, y);

                ItemComponent* item = create_component(engine, key_entity_id, COMP_ITEM);
                item->color = A;

                ArtComponent* art = create_component(engine, key_entity_id, COMP_ART);
                art->type = ART_KEY;
            }

            if (has_player) {
                EntityId player_entity_id = get_new_entity_id(engine);

                GridLocationComponent* gridloc = create_component(engine, player_entity_id, COMP_GRIDLOCATION);
                glmc_ivec2_set(gridloc->pos, x, y);

                ArtComponent* art = create_component(engine, player_entity_id, COMP_ART);
                art->type = ART_PLAYER;

                create_component(engine, player_entity_id, COMP_INPUTRECEIVER);

                CameraLookAtComponent* cameralookat = create_component(engine, player_entity_id, COMP_CAMERA_LOOK_AT);
                glmc_vec3_set(cameralookat->pos, x * 1.0f, y * 1.0f, 0.0f);

                CameraLookFromComponent* cameralookfrom = create_component(engine, player_entity_id, COMP_CAMERA_LOOK_FROM);
                cameralookfrom->distance = 15.0f;
                cameralookfrom->XYdegees = 0.0f;
                cameralookfrom->Zdegrees = 25.0f;
                glmc_vec3_set(cameralookfrom->pos, 4.0f, -4.0f, 4.0f); //this normally gets overridden by camera system
            }

            if (has_door) {
                EntityId door_entity_id = get_new_entity_id(engine);

                GridLocationComponent* gridloc = create_component(engine, door_entity_id, COMP_GRIDLOCATION);
                glmc_ivec2_set(gridloc->pos, x, y);

                ActivatableComponent* activatable = create_component(engine, door_entity_id, COMP_ACTIVATABLE);
                activatable->active = 0;

                DirectionComponent* directioncomponent = create_component(engine, door_entity_id, COMP_DIRECTION);
                directioncomponent->dir = N;

                ArtComponent* art = create_component(engine, door_entity_id, COMP_ART);
                art->type = ART_DOOR;
            }

            if (has_lock) {
                EntityId lock_entity_id = get_new_entity_id(engine);

                GridLocationComponent* gridloc = create_component(engine, lock_entity_id, COMP_GRIDLOCATION);
                glmc_ivec2_set(gridloc->pos, x, y);

                ActivatableComponent* activatable = create_component(engine, lock_entity_id, COMP_ACTIVATABLE);
                activatable->active = 0;

                ArtComponent* art = create_component(engine, lock_entity_id, COMP_ART);
                art->type = ART_LOCK;

                LockComponent* lock = create_component(engine, lock_entity_id, COMP_LOCK);
                lock->requiredKeyColor = B;
            }
        }
    }
}
