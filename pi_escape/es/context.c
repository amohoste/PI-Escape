#include "context.h"
#include "../../util/rgb_triple.h"

#include <stdlib.h>

void context_init(Context* c) {
    c->is_exit_game = 0;
    c->demo = 0;
    c->time = 0;
    c->level_ended = 0;
	c->fps = 0;
	c->temperature = 25;
	c->pressure = 1024;
	c->humidity = 35;
	c->wall_color[0] = 1.0f;
	c->wall_color[1] = 0.0f;
	c->wall_color[2] = 0.0f;
	c->wall_color[3] = 1.0f; 
	c->floor_color[0] = 1.0f;
	c->floor_color[1] = 0.0f;
	c->floor_color[2] = 0.0f;
	c->floor_color[3] = 1.0f; 
	c->world_color[0] = 0.0f;
	c->world_color[1] = 0.0f;
	c->world_color[2] = 0.25f;
    c->get =0;
    c->has =0;
    c->free =0;
    c->create =0;
	c->benchmarking = 0;
}

Context* context_alloc() {
    Context* res = malloc(sizeof(Context));
    context_init(res);
    return res;
}
void context_free(Context* c) {

}