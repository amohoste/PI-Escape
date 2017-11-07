#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "assemblage.h"


void create_level_entities(Level *l, Engine *engine) {
    // Lijst die ervoor zorgt dat het entityid van een connectie op een bepaalde locatie makkelijk kan worden opgevraagd
	EntityId **connectionEntityList;
    connectionEntityList = (EntityId **) calloc((size_t) l->height, sizeof(EntityId *));
    for (int i = 0; i < l->height; i++) {
        connectionEntityList[i] = (EntityId *) calloc((size_t) l->width, sizeof(EntityId));
    }

	// EntityList voor context
	EntityId **entityList;
	entityList = (EntityId **)calloc((size_t)l->height, sizeof(EntityId *));
	for (int i = 0; i < l->height; i++) {
		entityList[i] = (EntityId *)calloc((size_t)l->width, sizeof(EntityId));
	}

    engine->context.still_object_list = entityList;

	/* Aanmaken van alle componenten behalve verbindingsstukken */
    for (int x = 0; x < l->height; x++) {
        for (int y = 0; y < l->width; y++) {
            int has_door = IS_DOOR(x, y);
            int has_floor = !has_door;
            int has_ceil = !has_floor && !has_door;
            int has_key = IS_KEY(x, y);
            int has_player = IS_START(x, y);
            int has_lock = IS_LOCK(x, y);
            int has_wall = IS_WALL(x, y);
            int has_or = IS_OR(x, y);
            int has_and = IS_AND(x, y);
            int is_exit = IS_EXIT(x, y);

            int walls[4];
            walls[S] = y == 0 || has_wall;
            walls[N] = y == l->width - 1 || has_wall;
            walls[E] = x == l->height - 1 || has_wall;
            walls[W] = x == 0 || has_wall;

            if (has_player) {
                create_player_entity(engine, x, y);
            }

            if (has_door) {
                connectionEntityList[x][y] = create_door_entity(engine, l, x, y);
				entityList[x][y] = connectionEntityList[x][y];
            }
            if (has_lock) {
                connectionEntityList[x][y] = create_lock_entity(engine, x, y, l->spel[x][y]);
            }
            if (has_key) {
                create_key_entity(engine, x, y, l->spel[x][y]);
            }

            if (has_or) {
                connectionEntityList[x][y] = create_or_entity(engine, x, y);
            }

            if (has_and) {
                connectionEntityList[x][y] = create_and_entity(engine, x, y);
            }

            if (is_exit) {
                create_exit_entity(engine, x, y);
            }

            /* walls moeten altijd gemaakt worden voor de vloer enzo */
            EntityId wall = create_wall_entity(engine, l, x, y, has_floor, has_ceil, has_wall, walls);

			if(IS_WALL(x,y)){
				entityList[x][y] = wall;
			}

        }
    }

	// Alle verbindingsstukken aanmaken
	create_all_verbinding_entities(l, engine, connectionEntityList);

}

EntityId create_verbinding_entity(Engine *engine, Level *l, int x, int y, Direction direction) {
	EntityId verb_entity_id = get_new_entity_id(engine);

	GridLocationComponent *gridLoc = create_component(engine, verb_entity_id, COMP_GRIDLOCATION);
	glmc_ivec2_set(gridLoc->pos, x, y);

	ArtComponent *art = create_component(engine, verb_entity_id, COMP_ART);
	art->type = ART_CONNECTOR;

	DirectionComponent *dir = create_component(engine, verb_entity_id, COMP_DIRECTION);
	dir->dir = direction;

	create_component(engine, verb_entity_id, COMP_CONNECTIONS);

	ActivatableComponent *act = create_component(engine, verb_entity_id, COMP_ACTIVATABLE);
	act->active = 0;

	return verb_entity_id;
}

EntityId create_exit_entity(Engine *engine, int x, int y) {
    EntityId exit_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridLoc = create_component(engine, exit_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridLoc->pos, x, y);

    ArtComponent *art = create_component(engine, exit_entity_id, COMP_ART);
    art->type = ART_END;

    ExitComponent *exit = create_component(engine, exit_entity_id, COMP_EXIT);
}

EntityId create_and_entity(Engine *engine, int x, int y) {
    EntityId and_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, and_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, and_entity_id, COMP_ART);
    art->type = ART_CONNECTOR_AND;

    ConnectorLogicComponent *con = create_component(engine, and_entity_id, COMP_CONNECTORLOGIC);
	con->type = AND_LOGIC;

	create_component(engine, and_entity_id, COMP_CONNECTIONS);

    ActivatableComponent *act = create_component(engine, and_entity_id, COMP_ACTIVATABLE);
	act->active = 0;

    return and_entity_id;
}

EntityId create_or_entity(Engine *engine, int x, int y) {
    EntityId or_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, or_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, or_entity_id, COMP_ART);
    art->type = ART_CONNECTOR_OR;

    ConnectorLogicComponent *con = create_component(engine, or_entity_id, COMP_CONNECTORLOGIC);
	con->type = OR_LOGIC;

	create_component(engine, or_entity_id, COMP_CONNECTIONS);

    ActivatableComponent *act = create_component(engine, or_entity_id, COMP_ACTIVATABLE);
	act->active = 0;

    return or_entity_id;
}

EntityId create_player_entity(Engine *engine, int x, int y) {
    EntityId player_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, player_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, player_entity_id, COMP_ART);
    art->type = ART_PLAYER;

    create_component(engine, player_entity_id, COMP_INPUTRECEIVER);

    CameraLookAtComponent *cameralookat = create_component(engine, player_entity_id, COMP_CAMERA_LOOK_AT);
    glmc_vec3_set(cameralookat->pos, x * 1.0f, y * 1.0f, 0.0f);

    CameraLookFromComponent *cameralookfrom = create_component(engine, player_entity_id,
                                                               COMP_CAMERA_LOOK_FROM);
    cameralookfrom->distance = 15.0f;
    cameralookfrom->XYdegees = 0.0f;
    cameralookfrom->Zdegrees = 25.0f;
    glmc_vec3_set(cameralookfrom->pos, 4.0f, -4.0f, 4.0f); //this normally gets overridden by camera system

    MoveActionComponent *move = create_component(engine, player_entity_id, COMP_MOVE_ACTION);

	MoveHistoryComponent *moveHist = create_component(engine, player_entity_id, COMP_MOVE_HISTORY);

	engine->context.player = player_entity_id;

    return player_entity_id;
}

EntityId create_door_entity(Engine *engine, Level *l, int x, int y) {
    EntityId door_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, door_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ActivatableComponent *activatable = create_component(engine, door_entity_id, COMP_ACTIVATABLE);
    activatable->active = 0;

	create_component(engine, door_entity_id, COMP_CONNECTIONS);

    DirectionComponent *directioncomponent = create_component(engine, door_entity_id, COMP_DIRECTION);
    if ((x > 1 && IS_WALL(x - 1, y)) || (x < l->width - 1 && IS_WALL(x + 1, y))) {
        directioncomponent->dir = E;
    } else {
        directioncomponent->dir = N;
    }

    ArtComponent *art = create_component(engine, door_entity_id, COMP_ART);
    art->type = ART_DOOR;

    return door_entity_id;
}

EntityId create_lock_entity(Engine *engine, int x, int y, char color) {
    EntityId lock_entity_id = get_new_entity_id(engine);

	create_component(engine, lock_entity_id, COMP_CONNECTIONS);

    GridLocationComponent *gridloc = create_component(engine, lock_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ActivatableComponent *activatable = create_component(engine, lock_entity_id, COMP_ACTIVATABLE);
    activatable->active = 0;

    ArtComponent *art = create_component(engine, lock_entity_id, COMP_ART);
    art->type = ART_LOCK;

    LockComponent *lock = create_component(engine, lock_entity_id, COMP_LOCK);
    switch (color) {
        case 'A':
            lock->requiredKeyColor = A;
            break;
        case 'B':
            lock->requiredKeyColor = B;
            break;
        case 'C' :
            lock->requiredKeyColor = C;
            break;
        case 'O':
            lock->requiredKeyColor = O;
            break;
        default:
            break;
    }

    return lock_entity_id;
}

EntityId create_key_entity(Engine *engine, int x, int y, char color) {
    EntityId key_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, key_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ItemComponent *item = create_component(engine, key_entity_id, COMP_ITEM);
    switch (color) {
        case 'a':
            item->
                    color = A;
            break;
        case 'b':
            item->
                    color = B;
            break;
        case 'c' :
            item->
                    color = C;
            break;
        case 'o':
            item->
                    color = O;
            break;
        default:
            break;
    }

    ArtComponent *art = create_component(engine, key_entity_id, COMP_ART);
    art->type = ART_KEY;

	ItemActionComponent *itemaction = create_component(engine, key_entity_id, COMP_ITEMACTION);

    return key_entity_id;
}

EntityId
create_wall_entity(Engine *engine, Level *l, int x, int y, int has_floor, int has_ceil, int has_wall, int walls[4]) {

    EntityId wall_entity_id = get_new_entity_id(engine);

    GridLocationComponent *gridloc = create_component(engine, wall_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);

    ArtComponent *art = create_component(engine, wall_entity_id, COMP_ART);
    art->type = ART_WALL;

    WallArtComponent *wall = create_component(engine, wall_entity_id, COMP_WALLART);

    wall->has_floor = has_floor;
    wall->has_ceil = has_ceil || has_wall;
    wall->has_wall[S] = walls[S];
    wall->has_wall[N] = walls[N];
    wall->has_wall[E] = walls[E];
    wall->has_wall[W] = walls[W];
	
    if (x > 0 && wall->has_wall[W]) {
        create_wall(engine, x - 1, y, E);
    }
    if (x < l->height - 1 && wall->has_wall[E]) {
        create_wall(engine, x + 1, y, W);
    }
    if (y > 0 && wall->has_wall[S]) {
        create_wall(engine, x, y - 1, N);
    }
    if (y < l->width - 1 && wall->has_wall[N]) {
        create_wall(engine, x, y + 1, S);
    }

    return wall_entity_id;

}

void create_wall(Engine *engine, int x, int y, Direction direction) {
    EntityId wall_entity_id = get_new_entity_id(engine);
    GridLocationComponent *gridloc = create_component(engine, wall_entity_id, COMP_GRIDLOCATION);
    glmc_ivec2_set(gridloc->pos, x, y);
    ArtComponent *art = create_component(engine, wall_entity_id, COMP_ART);
    art->type = ART_WALL;
    WallArtComponent *wall = create_component(engine, wall_entity_id, COMP_WALLART);
    wall->has_wall[direction] = 1;

	BlockingComponent *block = create_component(engine, wall_entity_id, COMP_BLOCKING);
}

/*
 * Functies om de connectioncomponenten te initialiseren
 */

 /* Maakt alle verbindingsstukken aan */
void create_all_verbinding_entities(Level *l, Engine *engine, EntityId **connectionEntityList) {
	/*
	* Over het level lopen en voor elk slot alle volgende verbindingsstukken
	* aanmaken tot er een deur / logicastuk tegengekomen wordt
	*/
	for (int x = 0; x < l->height; x++) {
		for (int y = 0; y < l->width; y++) {
			int has_lock = IS_LOCK(x, y);

			// Als je lock tegenkomt
			if (has_lock) {
				ConnectionsComponent* connection = get_component(engine, connectionEntityList[x][y], COMP_CONNECTIONS);
				create_connections(l, engine, x, y, connectionEntityList, 0);
			}
		}
	}

	/*
	* Over het level lopen en voor elk logicastuk alle volgende verbindingsstukken
	* aanmaken tot er een deur / logicastuk tegengekomen wordt
	*/
	for (int x = 0; x < l->height; x++) {
		for (int y = 0; y < l->width; y++) {
			int has_logic = IS_OR(x, y) || IS_AND(x, y);

			// Als je logic tegenkomt
			if (has_logic) {
				ConnectionsComponent* connection = get_component(engine, connectionEntityList[x][y], COMP_CONNECTIONS);
				create_connections(l, engine, x, y, connectionEntityList, 1);
			}
		}
	}
}

/* Maakt de connecties aan vanaf een logicastuk / slot tot er een deur / logicastuk tegengekomen wordt */
void create_connections(Level *l, Engine *engine, int x, int y, EntityId **connectionEntityList, int logic) {
	// Vorige x en y
	int prevx = x;
	int prevy = y;
	Direction prevdir;
	EntityId id;
	DirectionComponent *dir;
	ConnectionsComponent *currConComp;

	// Connection component opvragen
	currConComp = get_component(engine, connectionEntityList[x][y], COMP_CONNECTIONS);

	if (logic) {
		id = create_first_verbinding_entity_logic(engine, l, currConComp, x, y);
	}
	else {
		id = create_first_verbinding_entity_lock(engine, l, x, y);
	}

	addDownStream(currConComp, id);
	currConComp = get_component(engine, id, COMP_CONNECTIONS);
	dir = get_component(engine, id, COMP_DIRECTION);
	prevdir = dir->dir;

	// Nieuwe locatie opvragen
	if (logic) {
		nextLocation_dir(&x, &y, &prevx, &prevy, prevdir);
	}
	else {
		nextLocation(&x, &y, &prevx, &prevy, l);
	}

	ArtComponent *art = get_component(engine, connectionEntityList[x][y], COMP_ART);

	// Blijven toevoegen tot we een deur / logic tegenkomen
	while (!(art->type == ART_CONNECTOR_AND || art->type == ART_CONNECTOR_OR || art->type == ART_DOOR)) {
		id = create_verbinding_entity_1(engine, l, x, y, prevdir);
		addDownStream(currConComp, id);
		currConComp = get_component(engine, id, COMP_CONNECTIONS);
		dir = get_component(engine, id, COMP_DIRECTION);
		prevdir = dir->dir;

		id = create_verbinding_entity_2(engine, l, x, y, prevdir);
		addDownStream(currConComp, id);
		currConComp = get_component(engine, id, COMP_CONNECTIONS);
		dir = get_component(engine, id, COMP_DIRECTION);
		prevdir = dir->dir;

		nextLocation(&x, &y, &prevx, &prevy, l);
		art = get_component(engine, connectionEntityList[x][y], COMP_ART);
	}

	if (art->type == ART_DOOR) {
		addDownStream(currConComp, connectionEntityList[x][y]);
		ConnectionsComponent *doorComp = get_component(engine, connectionEntityList[x][y], COMP_CONNECTIONS);
		addUpStream(doorComp, id);

	}
	else if (art->type == ART_CONNECTOR_AND || art->type == ART_CONNECTOR_OR) {
		id = create_verbinding_entity_1(engine, l, x, y, prevdir);
		addDownStream(currConComp, id);
		currConComp = get_component(engine, id, COMP_CONNECTIONS);
		addDownStream(currConComp, connectionEntityList[x][y]);

		// Upstream toevoegen
		ConnectionsComponent *logicConnComp = get_component(engine, connectionEntityList[x][y], COMP_CONNECTIONS);
		addUpStream(logicConnComp, id);
	}
}

/* Hulpfunctie die een verbindingsstuk cre�ert dat aan een logicastuk hangt, in de juiste richting */
EntityId create_first_verbinding_entity_logic(Engine *engine, Level *l, ConnectionsComponent *comp, int x, int y) {
	int n = 0;

	DirectionComponent* locations[3];
	if (comp->hasUpStream1) {
		DirectionComponent *dirCom = get_component(engine, comp->upstream[0], COMP_DIRECTION);
		locations[0] = dirCom;
		n += 1;
	}
	if (comp->hasUpStream2) {
		DirectionComponent *dirCom = get_component(engine, comp->upstream[1], COMP_DIRECTION);
		locations[1] = dirCom;
		n += 1;
	}
	if (comp->hasUpStream3) {
		DirectionComponent *dirCom = get_component(engine, comp->upstream[2], COMP_DIRECTION);
		locations[2] = dirCom;
		n += 1;
	}

	if (x >= 1 && IS_VERBINDING_DIRECTION(x - 1, y)) {
		// Kijken of deze component niet al een upstream van de logic is
		if (!dir_in(W, locations, n)) {
			return create_verbinding_entity(engine, l, x, y, W);
		}
	}
	if (x < l->height - 1) {
		if (IS_VERBINDING_DIRECTION(x + 1, y)) {
			// Kijken of deze component niet al een upstream van de logic is
			if (!dir_in(E, locations, n)) {
				return create_verbinding_entity(engine, l, x, y, E);
			}
		}
	}
	if (y >= 1 && IS_VERBINDING_DIRECTION(x, y - 1)) {
		// Kijken of deze component niet al een upstream van de logic is
		if (!dir_in(S, locations, n)) {
			return create_verbinding_entity(engine, l, x, y, S);
		}
	}
	if (y < l->width - 1 && IS_VERBINDING_DIRECTION(x, y + 1)) {
		// Kijken of deze component niet al een upstream van de logic is
		if (!dir_in(N, locations, n)) {
			return create_verbinding_entity(engine, l, x, y, N);
		}
	}
}

/* Hulpfunctie die een verbindingsstuk cre�ert dat aan een slot hangt, in de juiste richting */
EntityId create_first_verbinding_entity_lock(Engine *engine, Level *l, int x, int y) {

	if (x >= 1 && IS_VERBINDING_DIRECTION(x - 1, y)) {
		return create_verbinding_entity(engine, l, x, y, W);
	}
	if (x < l->height - 1) {
		if (IS_VERBINDING_DIRECTION(x + 1, y)) {
			return create_verbinding_entity(engine, l, x, y, E);
		}
	}
	if (y >= 1 && IS_VERBINDING_DIRECTION(x, y - 1)) {
		return create_verbinding_entity(engine, l, x, y, S);
	}
	if (y < l->width - 1 && IS_VERBINDING_DIRECTION(x, y + 1)) {
		return create_verbinding_entity(engine, l, x, y, N);
	}

}

/* Hulpfunctie die een verbindingsstuk cre�ert in de juiste richting indien hij het eerste stuk is dat op een bepaalde co�rdinaat terechtkomt */
EntityId create_verbinding_entity_1(Engine *engine, Level *l, int x, int y, Direction lastdir) {
	if (lastdir == W) {
		return create_verbinding_entity(engine, l, x, y, E);
	}

	if (lastdir == E) {
		return create_verbinding_entity(engine, l, x, y, W);
	}

	if (lastdir == S) {
		return create_verbinding_entity(engine, l, x, y, N);
	}

	if (lastdir == N) {
		return create_verbinding_entity(engine, l, x, y, S);
	}
}

/* Hulpfunctie die een verbindingsstuk cre�ert in de juiste richting indien hij het tweede stuk is dat op een bepaalde co�rdinaat terechtkomt */
EntityId create_verbinding_entity_2(Engine *engine, Level *l, int x, int y, Direction lastdir) {
	if (x >= 1 && IS_VERBINDING_DIRECTION(x - 1, y)) {
		if (IS_VERBINDING_DIRECTION(x - 1, y)) {
			if (lastdir != W) {
				return create_verbinding_entity(engine, l, x, y, W);
			}
		}
	}
	if (x < l->height - 1) {
		if (IS_VERBINDING_DIRECTION(x + 1, y)) {
			if (lastdir != E) {
				return create_verbinding_entity(engine, l, x, y, E);
			}
		}
	}
	if (y >= 1 && IS_VERBINDING_DIRECTION(x, y - 1)) {
		if (lastdir != S) {
			return create_verbinding_entity(engine, l, x, y, S);
		}
	}
	if (y < l->width - 1 && IS_VERBINDING_DIRECTION(x, y + 1)) {
		if (lastdir != N) {
			return create_verbinding_entity(engine, l, x, y, N);
		}
	}
}

/* Hulpfunctie die de meegegeven x en y waarden aanpast naar de volgende locatie van een verbindingsstuk gegeven een richting */
void nextLocation_dir(int *curx, int *cury, int *prevx, int *prevy, Direction dir) {
	if (dir == W) {
		*prevx = *curx;
		*prevy = *cury;
		*curx = *curx - 1;
	}
	else if (dir == E) {
		*prevx = *curx;
		*prevy = *cury;
		*curx = *curx + 1;
	}
	else if (dir == S) {
		*prevx = *curx;
		*prevy = *cury;
		*cury = *cury - 1;
	}
	else if (dir == N) {
		*prevx = *curx;
		*prevy = *cury;
		*cury = *cury + 1;
	}
}

/* Hulpfunctie die de volgende locatie voor een verbindingsstuk berekent gegeven een level */
void nextLocation(int *curx, int *cury, int *prevx, int *prevy, Level *l) {
	if (*curx >= 1 && IS_VERBINDING_DIRECTION(*curx - 1, *cury)) {
		if (((*curx) - 1) != *prevx) {
			*prevx = *curx;
			*prevy = *cury;
			*curx = *curx - 1;
			return;
		}

	}

	if (*curx < l->height - 1 && *curx + 1 != *prevx) {
		if (IS_VERBINDING_DIRECTION(*curx + 1, *cury)) {
			*prevx = *curx;
			*prevy = *cury;
			*curx = *curx + 1;
			return;
		}
	}

	if (*cury >= 1 && IS_VERBINDING_DIRECTION(*curx, *cury - 1)) {
		if (*cury - 1 != *prevy) {
			*prevy = *cury;
			*prevx = *curx;
			*cury = *cury - 1;
			return;
		}
	}

	if (*cury < l->width - 1 && IS_VERBINDING_DIRECTION(*curx, *cury + 1)) {
		if (*cury + 1 != *prevy) {
			*prevy = *cury;
			*prevx = *curx;
			*cury = *cury + 1;
			return;
		}
	}
}

/* Hulpfunctie die kijkt of een bepaalde direction in een array van directioncomponenten zit */
int dir_in(Direction dir, DirectionComponent* locations[3], int n) {
	for (int i = 0; i < n; i++) {
		if (locations[i]->dir == dir) {
			return 1;
		}
	}
	return 0;
}

/* Hulpfunctie om een upstream aan een ConnectionsComponent toe te voegen */
void addUpStream(ConnectionsComponent* conn, EntityId id) {
	if (!conn->hasUpStream1) {
		conn->upstream[0] = id;
		conn->hasUpStream1 = 1;
	}
	else if (!conn->hasUpStream2) {
		conn->upstream[1] = id;
		conn->hasUpStream2 = 1;
	}
	else {
		conn->upstream[2] = id;
		conn->hasUpStream3 = 1;
	}
}

/* Hulpfunctie om een downstream aan een ConnectionsComponent toe te voegen */
void addDownStream(ConnectionsComponent* conn, EntityId id) {
	conn->downstream = id;
	conn->hasDownStream = 1;
}
