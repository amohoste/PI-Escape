#include "context.h"
#include "../../util/rgb_triple.h"

#include <stdlib.h>

void context_init(Context* c) {
    c->is_exit_game = 0;
    c->demo = 0;
    c->time = 0;
    c->level_ended = 0;
	c->fps = 0;
	c->temperature = 0;
	c->pressure = 0;
	c->humidity = 0;

    c->get =0;
    c->has =0;
    c->free =0;
    c->create =0;
}

Context* context_alloc() {
    Context* res = malloc(sizeof(Context));
    context_init(res);
    return res;
}
void context_free(Context* c) {

}