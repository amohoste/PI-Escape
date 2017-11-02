#include "input_system.h"

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../game_util.h"

InputSystem* system_input_alloc() {
    InputSystem* res = calloc(1, sizeof(InputSystem));
    system_input_init(res);
    return res;
}

void system_input_init(InputSystem* system) {
}


void system_input_free(InputSystem* system) {
    
}

static void handleKeyDown(InputSystem* system, Engine* engine, SDL_keysym *keysym, EntityId input_recv_entity_id)
{
	// search entity
	EntityIterator entityresolver;
	search_entity_1(engine, COMP_MOVE_ACTION, &entityresolver);
	while (next_entity(&entityresolver)) {
		EntityId entity_id = entityresolver.entity_id;
		assert(entity_id != NO_ENTITY);

		// get move component of the entity
		MoveActionComponent *move = get_component(engine, entity_id, COMP_MOVE_ACTION);

		// get item action component of the entity
		ItemActionComponent *itemaction = get_component(engine, entity_id, COMP_ITEMACTION);

		switch (keysym->sym) {
		case SDLK_ESCAPE:
			//ignore until key released
			break;
		case SDLK_KP_ENTER: //fall-through
		case SDLK_RETURN:   //fall-through
		case SDLK_SPACE: {
			itemaction->act = 1;
			break;
		}
		case SDLK_UP: {
			move->up = 1;
			break;
		}
		case SDLK_DOWN: {
			move->down = 1;
			break;
		}
		case SDLK_LEFT: {
			move->left = 1;
			break;
		}
		case SDLK_RIGHT: {
			move->right = 1;
			break;
		}
#ifndef RPI
		case SDLK_t: {
			if ((keysym->mod & KMOD_CTRL) && (keysym->mod & KMOD_SHIFT)) {
				// lower temperature value
				(&engine->context)->temperature -= 1;
			} else if (keysym->mod & KMOD_CTRL) {
				// increase temperature value
				(&engine->context)->temperature += 1;
			}
			break;
		}
		case SDLK_p: {
			if ((keysym->mod & KMOD_CTRL) && (keysym->mod & KMOD_SHIFT)) {
				// lower pressure value
				(&engine->context)->pressure -= 1;
			}
			else if (keysym->mod & KMOD_CTRL) {
				// increase pressure value
				(&engine->context)->pressure += 1;
			}
			break;
		}
		case SDLK_h: {
			if ((keysym->mod & KMOD_CTRL) && (keysym->mod & KMOD_SHIFT)) {
				// lower humidity value
				(&engine->context)->humidity -= 1;
			}
			else if (keysym->mod & KMOD_CTRL) {
				// increase humidity value
				(&engine->context)->humidity += 1;
			}
			break;
		}
#endif // RPI
		default:
			break;
		}
	}
}

static void handleKeyUp(InputSystem* system, Engine* engine, SDL_keysym *keysym, EntityId inputReceiverEntity)
{
	// search entity
	EntityIterator entityresolver;
	search_entity_1(engine, COMP_MOVE_ACTION, &entityresolver);
	while (next_entity(&entityresolver)) {

		EntityId entity_id = entityresolver.entity_id;
		assert(entity_id != NO_ENTITY);

		// get move component of the entity
		MoveActionComponent *move = get_component(engine, entity_id, COMP_MOVE_ACTION);

		// get item action component of the entity
		ItemActionComponent *itemaction = get_component(engine, entity_id, COMP_ITEMACTION);

		switch (keysym->sym) {
		case SDLK_ESCAPE: {
			engine->context.is_exit_game = 1;
			break;
		}
		case SDLK_KP_ENTER: //fall-through
		case SDLK_RETURN:   //fall-through
		case SDLK_SPACE: {
			itemaction->act = 0;
			break;
		}
		case SDLK_t: {


			break;
		}
		case SDLK_UP: {
			move->up = 0;
			break;
		}
		case SDLK_DOWN: {
			move->down = 0;
			break;
		}
		case SDLK_LEFT: {
			move->left = 0;
			break;
		}
		case SDLK_RIGHT: {
			move->right = 0;
			break;
		}
		default:
			break;
		}
	}
}

void system_input_update(InputSystem* system, Engine* engine) {
    EntityId input_recv_entity_id = search_first_entity_1(engine, COMP_INPUTRECEIVER);

    SDL_Event event;
    memset(&event, 0, sizeof(SDL_Event));
    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
            case SDL_KEYDOWN:
                /* Handle key presses. */
                handleKeyDown(system, engine, &event.key.keysym, input_recv_entity_id);
                break;
            case SDL_KEYUP:
                /* Handle key release. */
                handleKeyUp(system, engine, &event.key.keysym, input_recv_entity_id);
                break;
            case SDL_QUIT:
                /* Handle quit requests (like Ctrl-c). */
                engine->context.is_exit_game = 1;
                break;
            case SDL_MOUSEMOTION: {
                SDL_MouseMotionEvent *mouseMotionEvent = (SDL_MouseMotionEvent *) &event;
                //There are 2 mouse events we want to ignore:
                // - initially, an event is generated that moves the mouse from 0,0 to the current position
                // - then, each time SDL_WarpMouse is called, an event is generated for that call
                if ((mouseMotionEvent->x != mouseMotionEvent->xrel || mouseMotionEvent->y != mouseMotionEvent->yrel)
//                    &&
//                    (mouseMotionEvent->x != system->screenMidX || mouseMotionEvent->y != system->screenMidY)
                        ) {
//                    SDL_WarpMouse(screenMidX, screenMidY);

                    int buttonDown = mouseMotionEvent->state & SDL_BUTTON_LEFT;
                    
                    if (buttonDown) {
                        printf("Mouse dragged %f %f\n", mouseMotionEvent->xrel * 1.0f, mouseMotionEvent->yrel * 1.0f);
						CameraLookFromComponent* cameraLookFrom = search_first_component(engine, COMP_CAMERA_LOOK_FROM);
						cameraLookFrom->XYdegees = fmodf((cameraLookFrom->XYdegees + (mouseMotionEvent->xrel) / 5.0f), 360.0f);
						cameraLookFrom->Zdegrees = fmodf((cameraLookFrom->Zdegrees + (mouseMotionEvent->yrel) / 5.0f), 360.0f);
                    } else {
                        //printf("Mouse moved %f %f\n", mouseMotionEvent->xrel * 1.0f, mouseMotionEvent->yrel * 1.0f);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                //SDL 1.2 handles the wheel in a silly way
                switch (event.button.button) {
                    case SDL_BUTTON_WHEELUP: {
                        printf("Wheel up\n");
                        break;
                    }
                    case SDL_BUTTON_WHEELDOWN:{
                        printf("Wheel down\n");
                        break;
                    }
                }
                break;
            }
        }



        
    }
}
