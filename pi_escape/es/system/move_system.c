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
    //TODO
}


void system_move_free(MoveSystem* system) {
    //TODO
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

		// TODO continue moving while key is pressed down
		// TODO check movehistory
		// TODO check walls & doors
		// TODO check width and height of level
		//int width = 10;
		//int height = 7;

		// Change location
		int x = grid_comp->pos[0];
		int y = grid_comp->pos[1];
		if (move_comp->up) {
			x = x - 1;
			move_comp->up = 0;
		} else if (move_comp->right) {
			y = y + 1;
			move_comp->right = 0;
		} else if (move_comp->down) {
			x = x + 1;
			move_comp->down = 0;
		} else if (move_comp->left) {
			y = y - 1;
			move_comp->left = 0;
		}

		// Move
		if (10 >= x && x >= 0 && 7 >= y && y >= 0) glmc_ivec2_set(grid_comp->pos, x, y);
	}

	/*
	// Gridlocationcomponent van deze entity opvragen
	GridLocationComponent* lookat_grid_comp = get_component(engine, lookat_entity_id, COMP_GRIDLOCATION);

	// printf("position = (%f,%f,%f)\n", cameraLookAt->pos[0], cameraLookAt->pos[1], cameraLookAt->pos[2]);
	float x = lookat_grid_comp->pos[0] * 1.0f;
	float y = lookat_grid_comp->pos[1] * 1.0f;
	glmc_vec3_set(cameraLookAt->pos, x, y, 0.0f);

	// Positie van waar gekeken wordt
	float distance = cameraLookFrom->distance;
	float xydegrees = cameraLookFrom->XYdegees;
	float zdegrees = cameraLookFrom->Zdegrees;

	glmc_vec3_set(cameraLookFrom->pos, distance * sinf(zdegrees) * cosf(xydegrees), distance * sinf(zdegrees) * sinf(xydegrees), distance * cosf(zdegrees));
	*/
}

/*
 * Check if the position at coords (x,y) is available for the player
 * 
 * returns 1 if the position is available
 *         0 if the position isn't available
 */
int availablePosition(MoveSystem* system, Engine* engine, int x, int y) {
	// TODO
}

