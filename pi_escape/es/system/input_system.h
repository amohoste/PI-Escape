/***************************************************************
- Input System -
Afhandelen van toetsenbord en muis input via SDL. Dit voegt 
MoveActionComponent en ItemActionComponent toe wanneer nodig.
Het vangt tevens toetsenbord input op voor sensor emulatie als 
er geen echte sensoren aanwezig zijn.
****************************************************************/

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <stdint.h>

typedef struct InputSystem {
    uint32_t screenWidth;
    uint32_t screenHeight;
    uint32_t screenMidX;
    uint32_t screenMidY;
} InputSystem;

#include "../engine.h"

void system_input_init(InputSystem*);
InputSystem* system_input_alloc();
void system_input_update(InputSystem*, Engine*);
void system_input_free(InputSystem*);

#endif //INPUT_SYSTEM_H