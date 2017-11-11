#ifdef RPI

#include <stdlib.h>
#include <stdio.h>
#include "led_system.h"
#include "../../led/sense_led.h"
#include "../assemblage.h"


LedSystem *system_led_alloc() {
	LedSystem *res = calloc(1, sizeof(LedSystem));
	system_led_init(res);
	return res;
}

void system_led_init(LedSystem *system) {
	//TODO
}


void system_led_free(LedSystem *system) {
	//TODO
}

void system_led_update(LedSystem *system, Engine *engine) {
	EntityIterator key_it;
	search_entity_1(engine, COMP_INCONTAINER, &key_it);
	if (!next_entity(&key_it)) {
		clear_ledgrid();
		return;
	}
	EntityId key_entity_id = key_it.entity_id;

	ItemComponent *item = get_component(engine, key_entity_id, COMP_ITEM);
	switch (item->color) {
	case A:
		build_one_color((SPGM_RGBTRIPLE) { .rgbRed = 0, .rgbGreen = 0, .rgbBlue = 255 });
		break;
	case B:
		build_one_color((SPGM_RGBTRIPLE) { .rgbRed = 0, .rgbGreen = 255, .rgbBlue = 0 });
		break;
	case C:
		build_one_color((SPGM_RGBTRIPLE) { .rgbRed = 255, .rgbGreen = 0, .rgbBlue = 0 });
		break;
	case O:
		build_rainbow();
		break;
	default:
		clear_ledgrid();
		break;
	}
}
#endif // RPI
