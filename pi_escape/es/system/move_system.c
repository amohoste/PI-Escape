/***************************************************************
- Move System -
Zoekt entities met een MoveActionComponent, en voert de beweging
uit indien mogelijk. Hierbij wordt rekening gehouden met
animaties, en met de MoveHistoryComponent die de vorige beweging
bijhoudt. Als twee pijltjestoetsen tegelijk ingedrukt worden,
zal elke richting afwisselend gekozen worden om zo diagonaal
te bewegen en langs muren te bewegen tot de eerste opening.
****************************************************************/

#include "move_system.h"
#include "../assemblage.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

MoveSystem* system_move_alloc() {
    MoveSystem* res = calloc(1, sizeof(MoveSystem));
    system_move_init(res);
    return res;
}

void system_move_init(MoveSystem* system) {

}


void system_move_free(MoveSystem* system) {

}

void system_move_update(MoveSystem* system, Engine* engine) {
	// Entity zoeken met een MoveActionComponent

	EntityIterator moveaction_it;
	search_entity_1(engine, COMP_MOVE_ACTION, &moveaction_it);
	while (next_entity(&moveaction_it)) {
		EntityId moveaction_entity_id = moveaction_it.entity_id;
		assert(moveaction_entity_id != NO_ENTITY);

		// Gridlocationcomponent van deze entity opvragen
		GridLocationComponent* grid_comp = get_component(engine, moveaction_entity_id, COMP_GRIDLOCATION);

		// MoveActionComponent van deze entity opvragen
		MoveActionComponent* move_comp = get_component(engine, moveaction_entity_id, COMP_MOVE_ACTION);

		// MoveHistoryComponent van deze entity opvragen
		MoveHistoryComponent* move_hist_comp = get_component(engine, moveaction_entity_id, COMP_MOVE_HISTORY);

		// Als er geen animatie bezig is
		if (engine->es_memory.components[COMP_MOVE_ANIMATION][moveaction_entity_id].free) {

			// Verander locatie

			// Huidige locatie
			int x = grid_comp->pos[0];
			int y = grid_comp->pos[1];

			// Check voor diagonaal bewegen
			int notDiagonal = (move_comp->up + move_comp->down + move_comp->right + move_comp->left) != 2;
			Direction prev = move_hist_comp->previous;
			if (move_comp->up && (notDiagonal || prev != N)) {
				MoveAnimationComponent* moveanimation = create_component(engine, moveaction_entity_id, COMP_MOVE_ANIMATION);
				moveanimation->dir = N;
				move_hist_comp->previous = N;
				moveanimation->starttime = clock();
				x = x - 1;
			} else if (move_comp->down && (notDiagonal || prev != S)) {
				MoveAnimationComponent* moveanimation = create_component(engine, moveaction_entity_id, COMP_MOVE_ANIMATION);
				moveanimation->dir = S;
				move_hist_comp->previous = S;
				moveanimation->starttime = clock();
				x = x + 1;
			} else if (move_comp->right && (notDiagonal || prev != E)) {
				MoveAnimationComponent* moveanimation = create_component(engine, moveaction_entity_id, COMP_MOVE_ANIMATION);
				moveanimation->dir = E;
				move_hist_comp->previous = E;
				moveanimation->starttime = clock();
				y = y + 1;
			} else if (move_comp->left && (notDiagonal || prev != W)) {
				MoveAnimationComponent* moveanimation = create_component(engine, moveaction_entity_id, COMP_MOVE_ANIMATION);
				moveanimation->dir = W;
				move_hist_comp->previous = W;
				moveanimation->starttime = clock();
				y = y - 1;
			}

			// Beweeg
			if (availablePosition(system, engine, x, y)) glmc_ivec2_set(grid_comp->pos, x, y);
		}
	}
}

/*
 * Collision detection voor de positie op coords (x,y)
 * 
 * returns 1 als plaats vrij is
 *         0 als plaats niet vrij is
 */
int availablePosition(MoveSystem* system, Engine* engine, int x, int y) {
	Context* ctx = &(engine->context);
	Level* l = ctx->current_level;

	int width = l->width;
	int height = l->height;

	int available = 1;

	// check positie
	if (l->height > x && x >= 0 && l->width > y && y >= 0) {
		char place = l->spel[x][y];

		if (IS_WALL(x, y)) available = 0;
		if (IS_DOOR(x, y) && doorIsClosed(system, engine, x, y)) available = 0;
	}
	else {
		// positie is out of bounds
		available = 0;
	}

	return available;
}

/*
* Check of de deur op de gegeven deur gestolen is
*
* returns 1 als gesloten
*         0 als open (of als er geen deur is)
*/
int doorIsClosed(MoveSystem* system, Engine* engine, int x, int y) {
	Context* ctx = &(engine->context);
	Level* l = ctx->current_level;

	EntityId door = engine->context.still_object_list[x][y];
	ActivatableComponent* actcomp = get_component(engine, door, COMP_ACTIVATABLE);

	return actcomp->active == 0;
}