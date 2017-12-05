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

    gc->createIntro();

    // Fontmanager aanmaken
    FontManager m(graphics);

    const shared_ptr<MenuDefinition> &ptr = gc->createGameMenu();
    MenuModel *model = new MenuModel;
    MenuController *controller = new MenuController;
    MenuView *view = new MenuView;
    LevelObserver *levelObserver = new LevelObserver;
    levelObserver->setMenuModel(model);
    model->registerObserver(LEVEL,levelObserver);
    model->addListener(view);
    view->setModel(model);
    controller->setMenuModel(model);
    view->setFontManager(&m);
    view->setGraphics(graphics);
    view->setController(controller);
    model->setMenuDefinition(ptr);

    delete gc;

    m.free(); // Fontmanager moet vrijgemaakt worden voor de graphics vrijgemaakt worden!

    graphics_free(graphics);
    free(graphics);
    return 0;
}





