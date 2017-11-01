#include "camera_system.h"


#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

CameraSystem* system_camera_alloc() {
    CameraSystem* res = calloc(1, sizeof(CameraSystem));
    system_camera_init(res);
    return res;
}

void system_camera_init(CameraSystem* system) {
    //TODO
}


void system_camera_free(CameraSystem* system) {
	//TODO
}

void system_camera_update(CameraSystem* system, Engine* engine) {
	CameraLookFromComponent* cameraLookFrom = search_first_component(engine, COMP_CAMERA_LOOK_FROM);
	CameraLookAtComponent* cameraLookAt = search_first_component(engine, COMP_CAMERA_LOOK_AT);

	// Entity zoeken die CameraLookatComponent en GridLocationComponent bevat
	EntityIterator lookat_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_CAMERA_LOOK_AT, &lookat_it);
	next_entity(&lookat_it);
	EntityId lookat_entity_id = lookat_it.entity_id;
	assert(lookat_entity_id != NO_ENTITY);

	// Gridlocationcomponent van deze entity opvragen
	GridLocationComponent* lookat_grid_comp = get_component(engine, lookat_entity_id, COMP_GRIDLOCATION);

	float x = lookat_grid_comp->pos[0] * 1.0f;
	float y = lookat_grid_comp->pos[1] * 1.0f;
	float curx = cameraLookAt->pos[0];
	float cury = cameraLookAt->pos[1];

	// Calculate how much camera lookat should move / frame
	float fps = engine->context.fps;
	float move = 0.01 * (400 / fps);

	// Calculate new camera lookat
	if (curx != x || cury != y) {
		if (curx < x) {
			curx += move;
			curx = MIN(curx, x);
		} else if (curx > x) {
			curx -= move;
			curx = MAX(curx, x);
		}

		if (cury < y) {
			cury += move;
			cury = MIN(cury, y);
		}
		else if (cury > y) {
			cury -= move;
			cury = MAX(cury, y);
		}
		
	}
	// Set new camera lookat
	glmc_vec3_set(cameraLookAt->pos, curx , cury, 0.0f);

	// Positie van waar gekeken wordt
	float distance = cameraLookFrom->distance;
	float xydegrees = cameraLookFrom->XYdegees;
	float zdegrees = cameraLookFrom->Zdegrees;

	float dx = (distance * sinf(zdegrees) * cosf(xydegrees));
	float dy = (distance * sinf(zdegrees) * sinf(xydegrees));
	float dz = distance * cosf(zdegrees);

	glmc_vec3_set(cameraLookFrom->pos, curx + dx, cury + dy , 0.0f + dz);

}
