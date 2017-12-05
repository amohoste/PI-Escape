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

    const shared_ptr<MovieDefinition> &intro = gc->createIntro();
    MovieModel *mm = new MovieModel();
    MovieGLView *mv = new MovieGLView();
    mm->addListener(mv);
    mv->setMovieModel(mm);
    mv->setFontManager(&m);
    mm->setMovieDefinition(intro);

    const shared_ptr<MenuDefinition> &ptr = gc->createGameMenu();
    MenuModel *model = new MenuModel;
    MenuController *controller = new MenuController;
    MenuView *view = new MenuView;
    LevelObserver *levelObserver = new LevelObserver;
    levelObserver->setMenuModel(model);
    model->registerObserver(LEVEL, levelObserver);
    model->addListener(view);
    view->setModel(model);
    controller->setMenuModel(model);
    view->setFontManager(&m);
    view->setController(controller);
    model->setMenuDefinition(ptr);

    delete gc;

    m.free(); // Fontmanager moet vrijgemaakt worden voor de graphics vrijgemaakt worden!

    graphics_free(graphics);
    free(graphics);
    return 0;
}





