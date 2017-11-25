#define __STDC_FORMAT_MACROS

#ifdef __cplusplus
extern "C"
{
#endif

#include "pi_escape/graphics/opengl_game_renderer.h"
#include "pi_escape/es/game.h"

#ifdef __cplusplus
}
#endif

#include "pi_escape\anim\FontManager.h"
#include <SDL.h>
#undef main //Weird bug on windows where SDL overwrite main definition

#include <stdlib.h>  
#include <crtdbg.h> 
#include <SDL_timer.h>
#include <string>

using namespace std;

int main() {
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        fatal("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    Graphics* graphics = graphics_alloc(0, 0);
	
    t_vec4 col = { 1.0f, 0.0f, 0.0f, 1.0f };

	FontManager m(graphics);
	
	m.loadFont("zorque", "zorque72.png", "zorque72.fnt");
	//m.loadFont("base", "base72.png", "base72.fnt");
	//m.loadFont("arcade", "arcade72.png", "arcade72.fnt");

	m.setFont("zorque");
	vector<GlyphDrawCommand> result = m.makeGlyphDrawCommands("Pack my box with five dozen liquor jugs.1234567890°,./;-_", 0, 500);

    //this is a demo of gl_glyph_draw

    Uint32 start_time_ms = SDL_GetTicks();
    Uint32 diff_time_ms = 0;
    while (diff_time_ms < 500) {
        graphics_begin_draw(graphics);

        glmc_vec4_set(col, diff_time_ms / 5000.0f, 0.0f, 0.0f, 1.0f);

		vector<GlyphDrawCommand>::iterator i = result.begin();
		
		while (i != result.end()) {
			m.draw(*i);
			i++;
		}
		
        graphics_end_draw(graphics);

        Uint32 cur_time_ms = SDL_GetTicks();
        diff_time_ms = cur_time_ms - start_time_ms;
    }

	m.free();
    graphics_free(graphics);
    free(graphics);
    return 0;
}
