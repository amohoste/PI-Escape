#define __STDC_FORMAT_MACROS

#include <inttypes.h>
#include <stdio.h>

#include "util/sleep.h"
#include "pi_escape/graphics/opengl_game_renderer.h"
#include "pi_escape/level/levelloader.h"
#include "pi_escape/es/game.h"
#include "util/min_unit.h"
#include "pi_escape/level/levelloadertester.h"

#include <SDL.h>

#undef main //Weird bug on windows where SDL overwrite main definition

#include <SDL_timer.h>


/*
* Create component
*/
static char *test_memory_manager_create_component() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    create_component(&pi_escape_2->engine, entity, COMP_ITEM);
    mu_assert(has_component(&pi_escape_2->engine, entity, COMP_ITEM));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

/*
* Has component
*/
static char *test_memory_manager_has_component_true() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    create_component(&pi_escape_2->engine, entity, COMP_ITEM);
    //het component mag nu niet free zijn
    mu_assert(!pi_escape_2->engine.es_memory.components[COMP_ITEM][entity].free);
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

static char *test_memory_manager_has_component_false() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    create_component(&pi_escape_2->engine, entity, COMP_ITEM);
    //het component mag nu niet free zijn
    mu_assert(!has_component(&pi_escape_2->engine, entity, COMP_EXIT));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

static char *test_memory_manager_has_component_has() {
	Graphics *g = graphics_alloc(0, 0);
	Game *pi_escape_2 = game_alloc(g);
	EntityId entity = get_new_entity_id(&pi_escape_2->engine);
	create_component(&pi_escape_2->engine, entity, COMP_ITEM);
	//het component mag nu niet free zijn
	mu_assert(has_component(&pi_escape_2->engine, entity, COMP_ITEM));
	game_free(pi_escape_2);
	free(pi_escape_2);
	graphics_free(g);
	free(g);
	return 0;
}

static char *test_memory_manager_has_component_multi() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    create_component(&pi_escape_2->engine, entity, COMP_ITEM);

    for (int i = 0; i < 100; ++i) {
        create_component(&pi_escape_2->engine, get_new_entity_id(&pi_escape_2->engine), COMP_LOCK);
    }

    //het component mag nu niet free zijn
    mu_assert(has_component(&pi_escape_2->engine, entity, COMP_ITEM));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}


static char *test_memory_manager_has_component(){
    mu_run_test(test_memory_manager_has_component_false);
    mu_run_test(test_memory_manager_has_component_true);
    mu_run_test(test_memory_manager_has_component_multi);
    return 0;
}


/*
* Get component
*/
static char *test_memory_manager_get_component_simple() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    void *itemComponent = create_component(&pi_escape_2->engine, entity, COMP_ITEM);
    mu_assert(itemComponent == get_component(&pi_escape_2->engine, entity, COMP_ITEM));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

static char *test_memory_manager_get_component_multi_components() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    void *itemComponent = create_component(&pi_escape_2->engine, entity, COMP_CAMERA_LOOK_AT);
    create_component(&pi_escape_2->engine, entity, COMP_EXIT);
    create_component(&pi_escape_2->engine, entity, COMP_ART);
    mu_assert(itemComponent == get_component(&pi_escape_2->engine, entity, COMP_CAMERA_LOOK_AT));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

static char *test_memory_manager_get_component(){
    mu_run_test(test_memory_manager_get_component_simple);
    mu_run_test(test_memory_manager_get_component_multi_components);
    return 0;
}

/*
* Free component
*/
static char *test_memory_manager_free_component() {
    Graphics *g = graphics_alloc(0, 0);
    Game *pi_escape_2 = game_alloc(g);
    EntityId entity = get_new_entity_id(&pi_escape_2->engine);
    create_component(&pi_escape_2->engine, entity, COMP_ITEM);
    free_component(&pi_escape_2->engine, entity, COMP_ITEM);
    mu_assert(!has_component(&pi_escape_2->engine, entity, COMP_ITEM));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

/*
* Search entity
*/
static char *test_memory_manager_search_entity_1() {
	Graphics *g = graphics_alloc(0, 0);
	Game *pi_escape_2 = game_alloc(g);
	EntityId entity1 = get_new_entity_id(&pi_escape_2->engine);
	EntityId entity2 = get_new_entity_id(&pi_escape_2->engine);
	create_component(&pi_escape_2->engine, entity1, COMP_CONNECTIONS);
	create_component(&pi_escape_2->engine, entity2, COMP_ITEM);
	create_component(&pi_escape_2->engine, entity2, COMP_INPUTRECEIVER);
	create_component(&pi_escape_2->engine, entity2, COMP_LOCK);

	EntityIterator comp_it;
	search_entity_1(&pi_escape_2->engine, COMP_CONNECTIONS, &comp_it);
	next_entity(&comp_it);

	EntityId comp = comp_it.entity_id;
	mu_assert(comp == entity1);

	game_free(pi_escape_2);
	free(pi_escape_2);
	graphics_free(g);
	free(g);
	return 0;
}

static char *test_memory_manager_search_entity_2() {
	Graphics *g = graphics_alloc(0, 0);
	Game *pi_escape_2 = game_alloc(g);
	EntityId entity1 = get_new_entity_id(&pi_escape_2->engine);
	EntityId entity2 = get_new_entity_id(&pi_escape_2->engine);
	create_component(&pi_escape_2->engine, entity2, COMP_CONNECTIONS);
	create_component(&pi_escape_2->engine, entity1, COMP_ITEM);
	create_component(&pi_escape_2->engine, entity2, COMP_INPUTRECEIVER);
	create_component(&pi_escape_2->engine, entity1, COMP_LOCK);

	EntityIterator comp_it;
	search_entity_2(&pi_escape_2->engine, COMP_ITEM, COMP_LOCK, &comp_it);
	next_entity(&comp_it);

	EntityId comp = comp_it.entity_id;
	mu_assert(comp == entity1);

	game_free(pi_escape_2);
	free(pi_escape_2);
	graphics_free(g);
	free(g);
	return 0;
}

static char *test_memory_manager_search_entity_3() {
	Graphics *g = graphics_alloc(0, 0);
	Game *pi_escape_2 = game_alloc(g);
	EntityId entity1 = get_new_entity_id(&pi_escape_2->engine);
	EntityId entity2 = get_new_entity_id(&pi_escape_2->engine);
	EntityId entity3 = get_new_entity_id(&pi_escape_2->engine);
	create_component(&pi_escape_2->engine, entity1, COMP_CONNECTIONS);
	create_component(&pi_escape_2->engine, entity1, COMP_ITEM);
	create_component(&pi_escape_2->engine, entity1, COMP_INPUTRECEIVER);
	create_component(&pi_escape_2->engine, entity1, COMP_LOCK);
	create_component(&pi_escape_2->engine, entity2, COMP_CONTAINER);
	create_component(&pi_escape_2->engine, entity2, COMP_LOCK);
	create_component(&pi_escape_2->engine, entity3, COMP_CONNECTIONS);
	create_component(&pi_escape_2->engine, entity3, COMP_INPUTRECEIVER);
	create_component(&pi_escape_2->engine, entity3, COMP_MOVE_ACTION);
	create_component(&pi_escape_2->engine, entity3, COMP_ITEM);

	EntityIterator comp_it;
	search_entity_3(&pi_escape_2->engine, COMP_CONNECTIONS, COMP_MOVE_ACTION, COMP_ITEM, &comp_it);
	next_entity(&comp_it);

	EntityId comp = comp_it.entity_id;
	mu_assert(comp == entity3);

	game_free(pi_escape_2);
	free(pi_escape_2);
	graphics_free(g);
	free(g);
	return 0;
}


static char *test_memory_manager_search_entity() {
	mu_run_test(test_memory_manager_search_entity_1);
	mu_run_test(test_memory_manager_search_entity_2);
	mu_run_test(test_memory_manager_search_entity_3);
	return 0;
}

/*
* Load level
*/
static char *test_load_levels() {
    mu_assert(test_filesdimensions());
    mu_assert(test_game1());
    return 0;
}

static char *all_tests() {
    //Basic memory manager test
    mu_run_test(test_memory_manager_create_component);
    test_memory_manager_has_component();
    test_memory_manager_get_component();
    mu_run_test(test_memory_manager_free_component);
	test_memory_manager_search_entity();
    mu_run_test(test_load_levels);
    return 0;
}


int main() {
    printf("Running tests:\n\n");
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
        printf("\nAT LEAST ONE TEST FAILED\n");
    } else {
        printf("\nALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", mu_tests_run);

#ifdef _WIN32
    system("pause");
#endif

    return result != 0;
}
