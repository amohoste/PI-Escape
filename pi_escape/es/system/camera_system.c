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
    //TODO
	CameraLookFromComponent* cameraLookFrom = search_first_component(engine, COMP_CAMERA_LOOK_FROM);
	CameraLookAtComponent* cameraLookAt = search_first_component(engine, COMP_CAMERA_LOOK_AT);

	// Entity zoeken die CameraLookatComponent en GridLocationComponent bevat
	EntityIterator lookat_it;
	search_entity_2(engine, COMP_GRIDLOCATION, COMP_CAMERA_LOOK_AT, &lookat_it);
	next_entity(&lookat_it);
	EntityId lookat_entity_id = lookat_it.entity_id;
	assert(lookat_entity_id != NO_ENTITY);

	// positie van deze entity opslaan
	t_ivec2 lookat_grid_pos;
	GridLocationComponent* lookat_grid_comp = get_component(engine, lookat_entity_id, COMP_GRIDLOCATION);
	glmc_assign_ivec2(lookat_grid_pos, lookat_grid_comp->pos);

	// Nieuwe lookatpositie berekenen en aanpassen
	level_pos_to_world_pos2i(lookat_grid_pos, cameraLookAt->pos);

	// Positie van waar gekeken wordt
	float distance = cameraLookFrom->distance;
	float xydegrees = cameraLookFrom->XYdegees;
	float zdegrees = cameraLookFrom->Zdegrees;

	glmc_vec3_set(cameraLookFrom->pos, distance * sinf(zdegrees) * cosf(xydegrees), distance * sinf(zdegrees) * sinf(xydegrees), distance * cosf(zdegrees));
}
