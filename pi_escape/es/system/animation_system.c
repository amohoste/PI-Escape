#include "animation_system.h"


#include <stdlib.h>
#include <assert.h>

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
	// Alle entities met een OneTimeAnimationComponent zoeken
	/*
	EntityIterator onetime_anim_it;
	search_entity_1(engine, COMP_ONE_TIME_ANIMATION, &onetime_anim_it);
	while (next_entity(&onetime_anim_it)) {
		EntityId moveaction_entity_id = moveaction_it.entity_id;
		assert(moveaction_entity_id != NO_ENTITY);
	}
	*/
}
