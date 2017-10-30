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
    EntityIterator moveaction_it;
    EntityId speler_id;
    search_entity_1(engine, COMP_MOVE_ACTION, &moveaction_it);
    while (next_entity(&moveaction_it)) {
        speler_id = moveaction_it.entity_id;
    }

    // Gridlocationcomponent van deze entity opvragen
    GridLocationComponent *speler_grid = get_component(engine, speler_id, COMP_GRIDLOCATION);

    EntityIterator exit_it;
    EntityId exit_id;
    search_entity_1(engine, COMP_EXIT, &exit_it);
    while (next_entity(&exit_it)) {
        exit_id = exit_it.entity_id;
    }

    GridLocationComponent *exit_grid = get_component(engine, exit_id, COMP_GRIDLOCATION);

    if(speler_grid->pos[0] == exit_grid->pos[0] && speler_grid->pos[1] == exit_grid->pos[1]){
        //todo beter
        printf("de exit is bereikt");
    }

}
