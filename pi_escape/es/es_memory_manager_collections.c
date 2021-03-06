#include "es_memory_manager_collections.h"
#include "es_memory_manager.h"
#include "engine.h"

#include <stdlib.h>
#include <assert.h>

static int get_requires_component(uint32_t component_id_filter, ComponentId component_id);

void free_entity_list_iterator(EntityListIterator *eli) {
    if(eli != NULL) {
        //entitylist moet niet vrijgegeven worden want die wordt nog gebruikt door andere iterators
        eli->engine = NULL;
        eli->component_id_filter = 0;
        eli->entity_id = 0;
        eli->entity_list = NULL;
    }
}

void start_search_in_list(int x, int y, Engine *engine, EntityListIterator *eli) {
    assert(eli != NULL);
    eli->entity_list = &engine->es_memory.grid[x][y];
    eli->entity_id = (EntityId) -1;
    eli->entity_id_index = -1;
    eli->engine = engine;
    eli->component_id_filter = 0;
}

void add_component_constraint(EntityListIterator *eli, int amount, ...) {
    assert(eli != NULL);
    va_list lijst;
    uint32_t mask = eli->component_id_filter;
    va_start(lijst, amount);
    for (int i = 0; i < amount; ++i) {
        mask = set_requires_component(mask, va_arg(lijst, ComponentId));
    }
    va_end(lijst);

    eli->component_id_filter = mask;
}

/*
 * Zet de waarde van de mask eerst op 0, soort van reset
 */
void set_component_constraint(EntityListIterator *eli, int amount, ...) {
    eli->component_id_filter = 0;
    va_list lijst;
    uint32_t mask = eli->component_id_filter;
    va_start(lijst, amount);
    for (int i = 0; i < amount; ++i) {
        mask = set_requires_component(mask, va_arg(lijst, ComponentId));
    }
    va_end(lijst);
    eli->component_id_filter = mask;
}

int next_in_list_mask(EntityListIterator *eli) {
    ComponentList list;
    componentlist_init(3, &list);

    for (ComponentId i = (ComponentId) 0; i < COMPONENT_ID_SIZE; ++i) {
        if (get_requires_component(eli->component_id_filter, i)) {
            componentlist_add(&list, i);
        }
    }

    for (int index = eli->entity_id_index + 1; index < eli->entity_list->count; index++) {
        if (eli->component_id_filter != 0) {
            for (int component_id = 0; component_id < list.count; component_id++) {
                if (eli->engine->es_memory.components[list.component_ids[component_id]][eli->entity_list->entity_ids[index]].free) {
                    //no match. Try the next entity
                    goto next_entity_loop;
                }
            }
        }
        //all match, return it
        eli->entity_id_index = index;
        eli->entity_id = eli->entity_list->entity_ids[index];
        componentlist_free(&list);
        return 1;

        next_entity_loop:;
    }
    componentlist_free(&list);
    return 0;
}


void update_location(int old_x, int old_y, Engine *engine, EntityId entityId, int new_x, int new_y) {
    GridLocationComponent *component = get_component(engine, entityId, COMP_GRIDLOCATION);
    glmc_ivec2_set(component->pos, new_x, new_y);

    entitylist_remove(&engine->es_memory.grid[old_x][old_y], entityId);
    entitylist_add(&engine->es_memory.grid[new_x][new_y], entityId);
}

void search_component(Engine *engine,
                      ComponentId component_id,
                      ComponentIterator *res) {
    res->engine = engine;
    res->component_id = component_id;
    res->entity_id = (EntityId) -1; //bit of a hack
}

int next_component(ComponentIterator *res) {
//    for (EntityId entity_id = res->entity_id+1; entity_id < MAX_ENTITIES; entity_id++) {
    for (EntityId entity_id = res->entity_id + 1; entity_id < res->engine->es_memory.next_entity_id; entity_id++) {
        if (!res->engine->es_memory.components[res->component_id][entity_id].free) {
            res->entity_id = entity_id;
            res->comp = &res->engine->es_memory.components[res->component_id][entity_id].camera_lookfrom;
            return 1;
        }
    }
    return 0;
}

void *search_first_component(Engine *engine, ComponentId component_id) {
    ComponentIterator it;
    search_component(engine, component_id, &it);
    if (next_component(&it))
        return it.comp;
    else
        return NULL;
}


static int get_requires_component(uint32_t component_id_filter, ComponentId component_id) {
    uint32_t mask = (uint32_t) (1 << component_id);
    return (mask & component_id_filter) != 0;
}

uint32_t set_requires_component(uint32_t component_id_filter, ComponentId component_id) {
    uint32_t mask = (uint32_t) (1 << component_id);
    return component_id_filter | mask;
}


void search_entity(Engine *engine,
                   uint32_t component_id_filter,
                   EntityIterator *res) {
    res->engine = engine;
    res->component_id_filter = component_id_filter;
    res->entity_id = (EntityId) -1; //bit of a hack
}

void search_entity_1(Engine *engine,
                     ComponentId component_id1,
                     EntityIterator *res) {
    uint32_t component_id_filter = set_requires_component(0, component_id1);
    search_entity(engine, component_id_filter, res);
}

void search_entity_2(Engine *engine,
                     ComponentId component_id1,
                     ComponentId component_id2,
                     EntityIterator *res) {
    uint32_t component_id_filter = set_requires_component(0, component_id1);
    component_id_filter = set_requires_component(component_id_filter, component_id2);
    search_entity(engine, component_id_filter, res);
}

void search_entity_3(Engine *engine,
                     ComponentId component_id1,
                     ComponentId component_id2,
                     ComponentId component_id3,
                     EntityIterator *res) {
    uint32_t component_id_filter = set_requires_component(0, component_id1);
    component_id_filter = set_requires_component(component_id_filter, component_id2);
    component_id_filter = set_requires_component(component_id_filter, component_id3);
    search_entity(engine, component_id_filter, res);
}

EntityId search_first_entity_with_mask(Engine *engine, uint32_t component_id_filter) {
    EntityIterator it;
    search_entity(engine, component_id_filter, &it);
    if (next_entity(&it))
        return it.entity_id;
    else
        return NO_ENTITY;
}

EntityId search_first_entity_1(Engine *engine, ComponentId component_id1) {
    uint32_t component_id_filter = set_requires_component(0, component_id1);
    return search_first_entity_with_mask(engine, component_id_filter);
}

EntityId search_first_entity_2(Engine *engine, ComponentId component_id1, ComponentId component_id2) {
    uint32_t component_id_filter = set_requires_component(0, component_id1);
    component_id_filter = set_requires_component(component_id_filter, component_id2);
    return search_first_entity_with_mask(engine, component_id_filter);
}

EntityId
search_first_entity_3(Engine *engine, ComponentId component_id1, ComponentId component_id2, ComponentId component_id3) {
    uint32_t component_id_filter = set_requires_component(0, component_id1);
    component_id_filter = set_requires_component(component_id_filter, component_id2);
    component_id_filter = set_requires_component(component_id_filter, component_id3);
    return search_first_entity_with_mask(engine, component_id_filter);
}

int next_entity(EntityIterator *res) {
    ComponentList list;
    componentlist_init(3, &list);

    for (ComponentId i = 0; i < COMPONENT_ID_SIZE; ++i) {
        if (get_requires_component(res->component_id_filter, i)) {
            componentlist_add(&list, i);
        }
    }

    for (EntityId entity_id = res->entity_id + 1; entity_id < res->engine->es_memory.next_entity_id; entity_id++) {
        if (res->component_id_filter != 0) {
            for (int component_id = 0; component_id < list.count; component_id++) {
                if (res->engine->es_memory.components[list.component_ids[component_id]][entity_id].free) {
                    //no match. Try the next entity
                    goto next_entity_loop;
                }
            }
        }
        //all match, return it
        res->entity_id = entity_id;
        componentlist_free(&list);
        return 1;

        next_entity_loop:;
    }
    componentlist_free(&list);
    return 0;
}


void entitylist_init(int initial_size, EntityList *dest) {
    dest->allocated = initial_size < 16 ? 16 : initial_size;
    dest->entity_ids = malloc(dest->allocated * sizeof(EntityId));
    dest->count = 0;
    assert(dest->entity_ids != NULL);
}

void entitylist_free(EntityList *dest) {
    free(dest->entity_ids);
    dest->count = 0;
    dest->allocated = 0;
    dest->entity_ids = NULL;
}

void entitylist_add(EntityList *dest, EntityId entity_id) {
    if (dest->count + 1 == dest->allocated) {
        entitylist_bigger(dest);
    }
    dest->entity_ids[dest->count++] = entity_id;
}

void entitylist_remove(EntityList *dest, EntityId entityId) {
    for (int i = 0; i < dest->count; ++i) {
        if (dest->entity_ids[i] == entityId) {
            dest->entity_ids[i] = dest->entity_ids[dest->count - 1];
            dest->entity_ids[dest->count - 1] = 0;
        }
    }
    dest->count--;
}

void entitylist_bigger(EntityList *dest) {
    int new_size = dest->allocated > 0 ? dest->allocated * 2 : 16;
    dest->entity_ids = realloc(dest->entity_ids, new_size * sizeof(EntityId));
    dest->allocated = new_size;
}

void componentlist_init(int initial_size, ComponentList *dest) {
    dest->allocated = initial_size < 16 ? 16 : initial_size;
    dest->component_ids = malloc(dest->allocated * sizeof(ComponentId));
    dest->count = 0;
    assert(dest->component_ids != NULL);
}

void componentlist_free(ComponentList *dest) {
    free(dest->component_ids);
    dest->count = 0;
    dest->allocated = 0;
    dest->component_ids = NULL;
}

void componentlist_add(ComponentList *dest, ComponentId component_id) {
    if (dest->count + 1 == dest->allocated) {
        int new_size = dest->allocated > 0 ? dest->allocated * 2 : 16;
        dest->component_ids = realloc(dest->component_ids, new_size * sizeof(ComponentId));
        dest->allocated = new_size;
    }
    dest->component_ids[dest->count++] = component_id;
}


void entityqueue_init(EntityQueue *queue, EntityId first_entity_id) {
    queue->front = malloc(sizeof(EntityQueueLink));
    queue->front->entity_id = first_entity_id;
    queue->front->next = NULL;
    queue->front->prev = NULL;
    queue->back = queue->front;
    queue->size = 1;
}

void entityqueue_free(EntityQueue *queue) {
    while (!entityqueue_is_empty(queue)) {
        entityqueue_pop_front(queue);
    }
}

int entityqueue_is_empty(EntityQueue *queue) {
    return queue->size == 0;
}

void entityqueue_push_back(EntityQueue *queue, EntityId entity_id) {
    EntityQueueLink *extra = malloc(sizeof(EntityQueueLink));
    extra->entity_id = entity_id;
    extra->next = NULL;
    extra->prev = queue->back;
    if (queue->back != NULL)
        queue->back->next = extra;
    else
        queue->front = extra;
    queue->back = extra;
    queue->size++;
}

EntityId entityqueue_pop_front(EntityQueue *queue) {
    if (queue->size < 0)
        fatal("Can't pop empty queue");
    EntityQueueLink *orig_front = queue->front;
    queue->front = orig_front->next;
    if (queue->front == NULL)
        queue->back = NULL;
    else
        queue->front->prev = NULL;
    EntityId res = orig_front->entity_id;
    free(orig_front);
    queue->size--;
    return res;
}
