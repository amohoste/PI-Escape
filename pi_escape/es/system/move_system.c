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

#include <SDL_timer.h>

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

	for (int i = 0; i < engine->es_memory.players.count; ++i) {
		// Get player
		EntityId player = engine->es_memory.players.entity_ids[i];
		assert(player != NO_ENTITY);

		// Gridlocationcomponent van deze entity opvragen
		GridLocationComponent* grid_comp = get_component(engine, player, COMP_GRIDLOCATION);

		// MoveActionComponent van deze entity opvragen
		MoveActionComponent* move_comp = get_component(engine, player, COMP_MOVE_ACTION);

		// MoveHistoryComponent van deze entity opvragen
		MoveHistoryComponent* move_hist_comp = get_component(engine, player, COMP_MOVE_HISTORY);

		// Als er geen animatie bezig is
		if (engine->es_memory.components[COMP_MOVE_ANIMATION][player].free) {

			// Huidige locatie
			int x = grid_comp->pos[0];
			int y = grid_comp->pos[1];

			// Check voor diagonaal bewegen
			int notDiagonal = (move_comp->up + move_comp->down + move_comp->right + move_comp->left) != 2;
			Direction prev = move_hist_comp->previous;
			if (move_comp->up && (notDiagonal || prev != N) && availablePosition(system, engine, x - 1, y)) {
				MoveAnimationComponent* moveanimation = create_component(engine, player, COMP_MOVE_ANIMATION);
				moveanimation->position = 0.0f;
				move_hist_comp->previous = N;
				moveanimation->starttime = SDL_GetTicks();
				x = x - 1;
				glmc_ivec2_set(grid_comp->pos, x, y);
			}
			else if (move_comp->down && (notDiagonal || prev != S) && availablePosition(system, engine, x + 1, y)) {
				MoveAnimationComponent* moveanimation = create_component(engine, player, COMP_MOVE_ANIMATION);
				moveanimation->position = 0.0f;
				move_hist_comp->previous = S;
				moveanimation->starttime = SDL_GetTicks();
				x = x + 1;
				glmc_ivec2_set(grid_comp->pos, x, y);
			}
			else if (move_comp->right && (notDiagonal || prev != E) && availablePosition(system, engine, x, y + 1)) {
				MoveAnimationComponent* moveanimation = create_component(engine, player, COMP_MOVE_ANIMATION);
				moveanimation->position = 0.0f;
				move_hist_comp->previous = E;
				moveanimation->starttime = SDL_GetTicks();
				y = y + 1;
				glmc_ivec2_set(grid_comp->pos, x, y);
			}
			else if (move_comp->left && (notDiagonal || prev != W) && availablePosition(system, engine, x, y - 1)) {
				MoveAnimationComponent* moveanimation = create_component(engine, player, COMP_MOVE_ANIMATION);
				moveanimation->position = 0.0f;
				move_hist_comp->previous = W;
				moveanimation->starttime = SDL_GetTicks();
				y = y - 1;
				glmc_ivec2_set(grid_comp->pos, x, y);
			}
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

		if (isBlocking(system, engine, x, y)) available = 0;
		if (isDoor(system, engine, x, y) && doorIsClosed(system, engine, x, y) == 0) available = 1;
	}
	else {
		// positie is out of bounds
		available = 0;
	}

	return available;
}

/*
* Check of de plaats vrij is
*
* returns 1 als niet vrij
*         0 als vrij
*/
int isBlocking(MoveSystem* system, Engine* engine, int x, int y) {
	int blocking = 0;

	EntityListIterator eli;
	start_search_in_list(x, y, engine, &eli);
	add_component_constraint(&eli,1, COMP_BLOCKING);
	while (blocking == 0 && next_in_list_mask(&eli)) {
		EntityId entity = (&eli)->entity_id;
		if (has_component(engine, entity, COMP_BLOCKING)) blocking = 1;
	}
	// Listiterator free
	free_entity_list_iterator(&eli);

	return blocking;
}

/*
* Check of er op de plaats zich een deur bevindt
*
* returns 1 is een deur
*         0 is geen deur
*/
int isDoor(MoveSystem* system, Engine* engine, int x, int y) {
	int isDoor = 0;

	EntityListIterator eli;
	start_search_in_list(x, y, engine, &eli);
	add_component_constraint(&eli, 1, COMP_BLOCKING);
	while (isDoor == 0 && next_in_list_mask(&eli)) if (has_component(engine, (&eli)->entity_id, COMP_ACTIVATABLE)) isDoor = 1;

	// Listiterator free
	free_entity_list_iterator(&eli);

	return isDoor;
}

/*
* Check of de deur op de gegeven deur gestolen is
*
* returns 1 als gesloten
*         0 als open (of als er geen deur is)
*/
int doorIsClosed(MoveSystem* system, Engine* engine, int x, int y) {
	int isClosed = 0;

	EntityListIterator eli;
	start_search_in_list(x, y, engine, &eli);
	add_component_constraint(&eli, 1, COMP_ACTIVATABLE);
	while (isClosed == 0 && next_in_list_mask(&eli)) {
		ActivatableComponent* actcomp = get_component(engine, (&eli)->entity_id, COMP_ACTIVATABLE);
		if (actcomp->active == 0) isClosed = 1;
	}
	// Listiterator free
	free_entity_list_iterator(&eli);

	return isClosed;
}