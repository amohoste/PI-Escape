/***************************************************************
- Context -
Hulp struct waarin data wordt bijgehouden die niet tot ��n 
specifiek deel spel behoort, maar tot het gehele spel.
****************************************************************/

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>
#include "../../util/rgb_triple.h"

typedef struct Context {
    uint64_t time;
    int is_exit_game;
    int demo;
    //TODO: add other context fields
} Context;

void context_init(Context*);
Context* context_alloc();
void context_free(Context*);


#endif //CONTEXT_H