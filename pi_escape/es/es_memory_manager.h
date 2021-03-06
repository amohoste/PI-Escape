#ifndef PIESCAPE2_ES_MEMORY_MANAGER_H
#define PIESCAPE2_ES_MEMORY_MANAGER_H

#include "entity.h"
#define MAX_ENTITIES 500u

#include "component_structs.h"

typedef struct AllComponent {
    int free;

    union {
        CameraLookFromComponent camera_lookfrom;
        CameraLookAtComponent camera_lookat;
        MoveActionComponent move_action;
        GridLocationComponent gridlocation_component;
        OneTimeAnimationComponent onetimeanimation_component;
        MoveAnimationComponent moveanimation_component;
        WallArtComponent wallinfo_component;
        WalkComponent walk_component;
        BlockingComponent blocking_component;
        ItemComponent item_component;
        InContainerComponent incontainer_component;
        ContainerComponent container_component;
        ActivationComponent activation_component;
        ActivatableComponent activatable_component;
        ConnectionsComponent connections_component;
        LockComponent lock_component;
        ConnectorLogicComponent connectorlogic_component;
        InputReceiverComponent inputreceiver_component;
        MoveActionComponent moveaction_component;
        MoveHistoryComponent movehistory_component;
        ItemActionComponent itemaction_component;
        DirectionComponent direction_component;
        ArtComponent art_component;
        ExitComponent exit_component;
    };
} AllComponent;

/*
* Boekhouding spel, hierin wordt voor elke entity bijgehouden
* welke components deze heeft en hoe deze data bereikbaar is.
*/
typedef struct ESMemory {
    EntityId next_entity_id;

    AllComponent components[COMPONENT_ID_SIZE][MAX_ENTITIES];
    EntityList **grid;

    EntityList players;
} ESMemory;

void es_memory_manager_init(ESMemory*);
void es_memory_manager_free(ESMemory*);

#include "engine.h"

/*
* Basisoperaties op boekhouding spel
*/
int has_component(Engine* engine, EntityId entity_id, ComponentId component_id);
void* get_component(Engine* engine, EntityId entity_id, ComponentId component_id);

void* create_component(Engine* engine, EntityId entity_id, ComponentId component_id);
void free_component(Engine* engine, EntityId entity_id, ComponentId component_id);

EntityId get_new_entity_id(Engine* engine);

#endif //PIESCAPE2_ES_MEMORY_MANAGER_H
