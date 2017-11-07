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
    mu_assert(pi_escape_2->engine.es_memory.components[COMP_EXIT][entity].free);
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
    mu_assert(!pi_escape_2->engine.es_memory.components[COMP_ITEM][entity].free);
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
    void *itemComponent = create_component(&pi_escape_2->engine, entity, COMP_ITEM);
    create_component(&pi_escape_2->engine, entity, COMP_EXIT);
    create_component(&pi_escape_2->engine, entity, COMP_ART);
    mu_assert(itemComponent == get_component(&pi_escape_2->engine, entity, COMP_ITEM));
    game_free(pi_escape_2);
    free(pi_escape_2);
    graphics_free(g);
    free(g);
    return 0;
}

/*
 * Alle tests in veband met get_component
 */
static char* *test_memory_manager_get_component(){
    mu_run_test(test_memory_manager_get_component_simple);
    mu_run_test(test_memory_manager_get_component_multi_components);
    return 0;
}

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
