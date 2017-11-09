#include "animation_system.h"

#include <stdlib.h>
#include <assert.h>

#include <SDL_timer.h>

#define PLAYER_MOVE_MS 100	// player move animation takes this many ms

AnimationSystem* system_animation_alloc() {
    AnimationSystem* res = calloc(1, sizeof(AnimationSystem));
    system_animation_init(res);
    return res;
}

void system_animation_init(AnimationSystem* system) {
    //TODO
}


void system_animation_free(AnimationSystem* system) {
    //TODO
}



void system_animation_update(AnimationSystem* system, Engine* engine) {
	// Search all entities with an OneTimeAnimationComponent
	/*
	EntityIterator onetime_anim_it;
	search_entity_1(engine, COMP_ONE_TIME_ANIMATION, &onetime_anim_it);
	while (next_entity(&onetime_anim_it)) {
		EntityId moveaction_entity_id = moveaction_it.entity_id;
		assert(moveaction_entity_id != NO_ENTITY);
	}
	*/

	// Search all entities with a MoveAnimationComponent
	EntityIterator move_anim_it;
	search_entity_1(engine, COMP_MOVE_ANIMATION, &move_anim_it);
	while (next_entity(&move_anim_it)) {
		EntityId move_anim_entity_id = move_anim_it.entity_id;
		assert(move_anim_entity_id != NO_ENTITY);

		// Get MoveAnimationComponent
		MoveAnimationComponent* move_anim_comp = get_component(engine, move_anim_entity_id, COMP_MOVE_ANIMATION);

		// Update position
		Uint32 cur_time_ms = SDL_GetTicks();
		Uint32 diff_time_ms = cur_time_ms - move_anim_comp->starttime;
		move_anim_comp->position = (float) diff_time_ms / PLAYER_MOVE_MS;
		// Free component if animation is completed
		if (move_anim_comp->position >= 1) {
			// End animation
			free_component(engine, move_anim_entity_id, COMP_MOVE_ANIMATION);
		}
	}
}
