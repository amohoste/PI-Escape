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

#include "pi_escape/anim/FontManager.h"
#include "pi_escape/anim/GameUICreator.h"
#include <SDL.h>

#undef main //Weird bug on windows where SDL overwrite main definition

#include <SDL_timer.h>
#include <string>

using namespace std;

int main() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fatal("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    Graphics *graphics = graphics_alloc(0, 0);

    GameUICreator *gc = new GameUICreator;


    // Fontmanager aanmaken
    FontManager m(graphics);

    // Fonts inladen
    m.loadFont("zorque", "zorque72.png", "zorque72.fnt");
    m.loadFont("base", "base72.png", "base72.fnt");
    m.loadFont("arcade", "arcade72.png", "arcade72.fnt");

    MoviePlayer *mp = new MoviePlayer(&m);
//    mp->play(gc->createIntro());
    mp->play(gc->createOutro());
//    mp->play(gc->createCredits());

    MenuShower *ms = new MenuShower(&m);
    ms->show(gc->createGameMenu());

    delete gc;

    m.free(); // Fontmanager moet vrijgemaakt worden voor de graphics vrijgemaakt worden!

    graphics_free(graphics);
    free(graphics);
    return 0;
}





