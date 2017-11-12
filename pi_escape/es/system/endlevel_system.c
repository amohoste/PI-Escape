#include "endlevel_system.h"


#include <stdlib.h>

#include <stdio.h>
#include <assert.h>

EndLevelSystem *system_endlevel_alloc() {
    EndLevelSystem *res = calloc(1, sizeof(EndLevelSystem));
    system_endlevel_init(res);
    return res;
}

void system_endlevel_init(EndLevelSystem *system) {
    //TODO
}


void system_endlevel_free(EndLevelSystem *system) {
    //TODO
}

void system_endlevel_update(EndLevelSystem *system, Engine *engine) {

    for (int i = 0; i < engine->es_memory.players.count; ++i) {
        EntityId speler_id = engine->es_memory.players.entity_ids[i];
        GridLocationComponent *speler_grid = get_component(engine, speler_id, COMP_GRIDLOCATION);

        EntityId exit_id = search_first_entity_1(engine, COMP_EXIT);
        GridLocationComponent *exit_grid = get_component(engine, exit_id, COMP_GRIDLOCATION);

        if (speler_grid->pos[0] == exit_grid->pos[0] && speler_grid->pos[1] == exit_grid->pos[1]) {
            engine->context.level_ended = 1;
        }
    }
}
