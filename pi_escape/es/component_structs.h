#ifndef PIESCAPE2_COMPONENTS_H
#define PIESCAPE2_COMPONENTS_H
#define TO_IMPLEMENT_STRUCT char c


#include "entity.h"
#include "component_enums.h"
#include "es_memory_manager_collections.h"

#include "../level/levelloader.h"
#include "game_util.h"
#include "../../util/util.h"

#include <stdint.h>
#include <glmc.h>

#include <SDL_timer.h>

/*
* Positie van waaruit camera kijkt
*/
typedef struct CameraLookFromComponent {
    // Absolute positie camera
	t_vec3 pos;
    
	// Afstand en hoeken van de camera relatief tegenover 
	// de cameraLookAtComponent
    float distance;
    float XYdegees;
    float Zdegrees;
} CameraLookFromComponent;


/*
* Focus punt van de camera
*/
typedef struct CameraLookAtComponent {
    t_vec3 pos;
    
    uint64_t last_update;
} CameraLookAtComponent;

/*
* De intentie van een entity om te bewegen
*/
typedef struct MoveActionComponent {
	// Er kunnen meerdere richtingen tegelijk bijgehouden
	// worden (als speler 2 pijltjestoetsen ingedrukt houdt)
	int up;
	int right;
	int down;
	int left;
} MoveActionComponent;

/*
* Locatie van een entity in het spel
*/
typedef struct GridLocationComponent {
    t_ivec2 pos;
} GridLocationComponent;

/*
* Weergave van een ��nmalige animatie
*/
typedef struct OneTimeAnimationComponent {
    //TODO
	TO_IMPLEMENT_STRUCT;
} OneTimeAnimationComponent;

/*
* Weergave van een bewegingsanimatie
*/
typedef struct MoveAnimationComponent {
    //TODO
	float position;
	Uint32 starttime;
} MoveAnimationComponent;

/*
* Geeft aan dat entity locatie is die toegankelijk 
* is voor spelers en objecten.
*/
typedef struct WalkComponent {
	//TODO
	// Houdt geen velden bij (leeg)
	TO_IMPLEMENT_STRUCT;
} WalkComponent;

/*
* Entity heeft vloeren en / of muren
*/
typedef struct WallArtComponent {
    int has_ceil;
    int has_floor;
    int has_wall[4]; //indexed by Direction
} WallArtComponent;

/*
* Geeft aan of entity actief / inactief is
* om deze al dan niet te blokkeren
*/
typedef struct BlockingComponent {
    //TODO
	TO_IMPLEMENT_STRUCT;
} BlockingComponent;

/*
* Opraapbaar object met type en kleur
*/
typedef struct ItemComponent {
    ItemColor color;
    //TODO
} ItemComponent;

/*
* Container waarin entity zich bevindt
*/
typedef struct InContainerComponent {
    //TODO
	// Houdt geen velden bij (leeg)
	TO_IMPLEMENT_STRUCT;
} InContainerComponent;

/*
* Entity is container waarin andere entities
* kunnen zitten
*/
typedef struct ContainerComponent {
    //TODO
	TO_IMPLEMENT_STRUCT;
} ContainerComponent;

/*
* Activeren / deactiveren van een entity
*/
typedef struct ActivationComponent {
    //TODO
	TO_IMPLEMENT_STRUCT;
} ActivationComponent;

/*
* Al dan niet actief zijn van een entity
*/
typedef struct ActivatableComponent {
    int active;
} ActivatableComponent;

/*
* Verbinding van een entity met andere entities
*/
typedef struct ConnectionsComponent {
    //TODO
	// Houdt de "upstream" en "downstream" entity ID's bij
	EntityId upstream[3];
	int hasUpStream1;
	int hasUpStream2;
	int hasUpStream3;
	EntityId downstream;
	int hasDownStream;
} ConnectionsComponent;

/*
* Een slot
*/
typedef struct LockComponent {
    ItemColor requiredKeyColor;
} LockComponent;

/*
* Extra vereiste ivm. activeren geconnecteerde 
* entities (and/or logica)
*/
typedef struct ConnectorLogicComponent {
    //TODO
	LogicType type;
	TO_IMPLEMENT_STRUCT;
} ConnectorLogicComponent;

/*
* Geeft aan dat entity input ontvangt van muis en toetsenbord
*/
typedef struct InputReceiverComponent {
	int actkey;
} InputReceiverComponent;

/*
* Vorige beweging van de entity
*/
typedef struct MoveHistoryComponent {
	Direction previous;
} MoveHistoryComponent;

/*
* De intentie van een entity om een actie uit te voeren
*/
typedef struct ItemActionComponent {
	int act;	// bool act
} ItemActionComponent;

/*
* Richting entity (deuren en connectors hebben richting)
*/
typedef struct DirectionComponent {
    Direction dir;
} DirectionComponent;

/*
* Type entity (voor 3D weergave)
*/
typedef struct ArtComponent {
    ArtType type;
} ArtComponent;

/*
* Als speler op zelfde locatie als deze entity staat
* is level ten einde.
*/
typedef struct ExitComponent {
    //TODO
	// Houdt geen velden bij (leeg)
	TO_IMPLEMENT_STRUCT;
} ExitComponent;

#endif //PIESCAPE2_COMPONENTS_H
