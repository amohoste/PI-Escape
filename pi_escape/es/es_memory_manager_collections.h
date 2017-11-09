/***************************************************************
- Memory manager collections -
Functies om te zoeken binnen de memory manager 
(het geheugenbeheersysteem).
****************************************************************/

#ifndef PIESCAPE2_ENGINE_COLLECTIONS_H
#define PIESCAPE2_ENGINE_COLLECTIONS_H

typedef struct ComponentIterator ComponentIterator;
typedef struct EntityList EntityList;
typedef struct EntityIterator EntityIterator;
typedef struct Engine Engine;
typedef struct EntityListIterator EntityListIterator;

#include "entity.h"
#include "component_enums.h"

#include <stdint.h>

#define NO_ENTITY (0xFFFFFFFF)

typedef struct EntityListIterator{
    EntityId entity_id;
    uint32_t component_id_filter;
    EntityList *entity_list;
    int entity_id_index;
    Engine *engine;
} EntityListIterator;

void start_search_in_list(int x, int y, Engine *engine, EntityListIterator *eli, uint32_t component_mask);
int next_in_list_mask(EntityListIterator *eli);

typedef struct ComponentIterator {
    Engine* engine;
    EntityId entity_id;
    ComponentId component_id;
    void* comp;
} ComponentIterator;

void search_component(Engine* engine,
                      ComponentId component_id,
                      ComponentIterator* res);
int next_component(ComponentIterator*);

//returns a pointer to the component
void* search_first_component(Engine* engine, ComponentId component_id);


typedef struct EntityIterator {
    Engine* engine;
    EntityId entity_id;
    uint32_t component_id_filter;
} EntityIterator;


uint32_t set_requires_component(uint32_t component_id_filter, ComponentId component_id);

void search_entity(Engine* engine,
                   uint32_t component_id_filter,
                   EntityIterator* res);
int next_entity(EntityIterator*);

void search_entity_1(Engine* engine,
                     ComponentId component_id,
                     EntityIterator* res);
void search_entity_2(Engine* engine,
                     ComponentId component_id1,
                     ComponentId component_id2,
                     EntityIterator* res);
void search_entity_3(Engine* engine,
                     ComponentId component_id1,
                     ComponentId component_id2,
                     ComponentId component_id3,
                     EntityIterator* res);

EntityId search_first_entity_with_mask(Engine *engine, uint32_t component_id_filter);
EntityId search_first_entity_1(Engine* engine, ComponentId component_id);
EntityId search_first_entity_2(Engine* engine, ComponentId component_id, ComponentId component_id2);
EntityId search_first_entity_3(Engine* engine, ComponentId component_id, ComponentId component_id2, ComponentId component_id3);

typedef struct EntityList {
    EntityId* entity_ids;
    int count;
    int allocated;
} EntityList;

void entitylist_init(int initial_size, EntityList* dest);
void entitylist_free(EntityList* dest);
void entitylist_add(EntityList* dest, EntityId entity_id);

typedef struct ComponentList {
    ComponentId* component_ids;
    int count;
    int allocated;
} ComponentList;

void componentlist_init(int initial_size, ComponentList* dest);
void componentlist_free(ComponentList* dest);
void componentlist_add(ComponentList* dest, ComponentId component_id);



typedef struct EntityQueueLink {
    EntityId entity_id;
    struct EntityQueueLink* next;
    struct EntityQueueLink* prev;
} EntityQueueLink;

typedef struct EntityQueue {
    EntityQueueLink* front;
    EntityQueueLink* back;
    int size;
} EntityQueue;

void entityqueue_init(EntityQueue* queue, EntityId first_entity_id);
void entityqueue_free(EntityQueue* queue);
int entityqueue_is_empty(EntityQueue* queue);
void entityqueue_push_back(EntityQueue* queue, EntityId entity_id);
EntityId entityqueue_pop_front(EntityQueue* queue);


#endif //PIESCAPE2_ENGINE_COLLECTIONS_H
