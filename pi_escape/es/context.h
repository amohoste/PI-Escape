/***************************************************************
- Context -
Hulp struct waarin data wordt bijgehouden die niet tot ��n 
specifiek deel spel behoort, maar tot het gehele spel.
****************************************************************/

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>
#include "../../util/rgb_triple.h"
#include "../level/levelloader.h"

typedef struct Context {
    uint64_t time;
    int is_exit_game;
    int demo;
    Level *current_level;
    int level_ended;
	float fps;
    //TODO: add other context fields
} Context;

void context_init(Context*);
Context* context_alloc();
void context_free(Context*);


#endif //CONTEXT_H