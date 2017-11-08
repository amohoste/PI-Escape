#include "animation_system.h"

#include <stdlib.h>
#include <time.h>
#include <assert.h>

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

		// Free component if animation is completed
		clock_t now = clock();
		float passed_time_ms = ((float)(now - move_anim_comp->starttime) / CLOCKS_PER_SEC) * 1000;
		if (passed_time_ms >= PLAYER_MOVE_MS) {
			// End animation
			free_component(engine, move_anim_entity_id, COMP_MOVE_ANIMATION);
		}
	}
}
