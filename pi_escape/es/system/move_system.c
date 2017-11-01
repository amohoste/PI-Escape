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

#define PLAYER_MOVE_MS 100

MoveSystem* system_move_alloc() {
    MoveSystem* res = calloc(1, sizeof(MoveSystem));
    system_move_init(res);
    return res;
}

void system_move_init(MoveSystem* system) {
	system->player_moves = 0;
}


void system_move_free(MoveSystem* system) {

}

void system_move_update(MoveSystem* system, Engine* engine) {
	// Move if timer is 0
	if (system->player_moves == 0) {
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

			// TODO continue moving while key is pressed down
			// TODO check movehistory

			// Change location
			int x = grid_comp->pos[0];
			int y = grid_comp->pos[1];
			if (move_comp->up) {
				x = x - 1;
			}
			else if (move_comp->right) {
				y = y + 1;
			}
			else if (move_comp->down) {
				x = x + 1;
			}
			else if (move_comp->left) {
				y = y - 1;
			}

			// Move
			if (availablePosition(system, engine, x, y)) glmc_ivec2_set(grid_comp->pos, x, y);
		}

		// Reset timer
		system->player_moves = PLAYER_MOVE_MS;
	} else {
		system->player_moves = system->player_moves - 1;
	}
}

/*
 * Check if the position at coords (x,y) is available for the player
 * 
 * returns 1 if the position is available
 *         0 if the position isn't available
 */
int availablePosition(MoveSystem* system, Engine* engine, int x, int y) {
	Context* ctx = &(engine->context);
	Level* l = ctx->current_level;

	int width = l->width;
	int height = l->height;

	int available = 1;

	// check position
	if (l->height > x && x >= 0 && l->width > y && y >= 0) {
		char place = l->spel[x][y];

		if (IS_WALL(x, y)) available = 0;
		if (IS_DOOR(x, y) && doorIsClosed(system, engine, x, y)) available = 0;
	}
	else {
		// position is out of bounds
		available = 0;
	}

	return available;
}

/*
* Check if the door at the given position is closed
*
* returns 1 if closed
*         0 if open (or there isn't a door at the given position)
*/
int doorIsClosed(MoveSystem* system, Engine* engine, int x, int y) {
	Context* ctx = &(engine->context);
	Level* l = ctx->current_level;

	int closed = 1;

	// TODO

	return closed;
}