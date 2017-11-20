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
#include <SDL_timer.h>

#include <string>
#include <cassert>

using namespace std;

int main() {
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        fatal("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    Graphics* graphics = graphics_alloc(0, 0);

    GLGlyph glGlyph;
    gl_glyph_init(&glGlyph, graphics, (char*) "pi_escape/graphics/zorque72.png");

    t_vec4 col = { 1.0f, 0.0f, 0.0f, 1.0f };

	FontManager m(graphics);
	m.loadFont("zorque", "zorque72.png", "zorque72.fnt");
	m.loadFont("base", "base72.png", "base72.fnt");
	m.loadFont("arcade", "arcade72.png", "arcade72.fnt");
	vector<GlyphDrawCommand> result = m.makeGlyphDrawCommands("Pack my box with five dozen liquor jugs.1234567890�,./;-_", 0, 500);

    //this is a demo of gl_glyph_draw

    Uint32 start_time_ms = SDL_GetTicks();
    Uint32 diff_time_ms = 0;
    while (diff_time_ms < 5000) {
        graphics_begin_draw(graphics);

        glmc_vec4_set(col, diff_time_ms / 5000.0f, 0.0f, 0.0f, 1.0f);

		vector<GlyphDrawCommand>::iterator i = result.begin();
		m.setFont("zorque");
		while (i != result.end()) {
			m.draw(*i);
			i++;
		}
		
		/*
		gl_glyph_draw(&glGlyph, 481, 750, 2, 215, 48, 51, col);
		gl_glyph_draw(&glGlyph, 534, 751, 52, 109, 35, 51, col);
		gl_glyph_draw(&glGlyph, 570, 698, 214, 495, 51, 14, col);
		gl_glyph_draw(&glGlyph, 624, 750, 2, 215, 48, 51, col);
		gl_glyph_draw(&glGlyph, 677, 751, 52, 109, 35, 51, col);
		gl_glyph_draw(&glGlyph, 714, 751, 127, 268, 39, 52, col);
		gl_glyph_draw(&glGlyph, 757, 750, 53, 428, 41, 51, col);
		gl_glyph_draw(&glGlyph, 801, 751, 2, 268, 48, 52, col);
		gl_glyph_draw(&glGlyph, 852, 698, 214, 495, 51, 14, col);
		gl_glyph_draw(&glGlyph, 906, 750, 44, 56, 46, 51, col);
		gl_glyph_draw(&glGlyph, 954, 750, 82, 162, 41, 51, col);
		gl_glyph_draw(&glGlyph, 997, 751, 2, 2, 48, 52, col);
		gl_glyph_draw(&glGlyph, 1049, 751, 103, 215, 58, 51, col);
		gl_glyph_draw(&glGlyph, 1165, 750, 52, 2, 42, 51, col);
		gl_glyph_draw(&glGlyph, 1213, 751, 94, 335, 38, 52, col);
		gl_glyph_draw(&glGlyph, 1254, 751, 2, 2, 48, 52, col);
		gl_glyph_draw(&glGlyph, 1306, 750, 18, 322, 58, 51, col);
		gl_glyph_draw(&glGlyph, 1368, 750, 53, 428, 41, 51, col);
		gl_glyph_draw(&glGlyph, 1412, 751, 52, 109, 35, 51, col);
		gl_glyph_draw(&glGlyph, 1451, 750, 52, 2, 42, 51, col);
		*/
        graphics_end_draw(graphics);

        Uint32 cur_time_ms = SDL_GetTicks();
        diff_time_ms = cur_time_ms - start_time_ms;
    }

	

    gl_glyph_free(&glGlyph);
    graphics_free(graphics);
    free(graphics);

    return 0;
}
