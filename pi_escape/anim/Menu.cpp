#include "Menu.h"
#include "MenuBuilder.h"

#include <utility>
#include <assert.h>

using namespace std;


void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition = std::move(menuDefinition);
    this->selectedInt = 0;
    this->time = 0;
    this->done = false;
    this->fireInvalidationEvent();
}

shared_ptr<MenuDefinition> MenuModel::getMenuDefinition() {
    return this->menuDefinition;
}

void MenuModel::up() {
    selectedInt = selectedInt == 0 ? 0 : selectedInt - 1;
    fireInvalidationEvent();
    notify(SELECTION);
}

void MenuModel::down() {
    selectedInt = selectedInt == this->menuDefinition.get()->entries.size() - 1 ? selectedInt : selectedInt + 1;
    fireInvalidationEvent();
    notify(SELECTION);
}

void MenuModel::select() {
    getSelectedEntry()->function(this);
}

Entry *MenuModel::getSelectedEntry() {
    return getMenuDefinition().get()->entries[selectedInt];
}

vector<Level *> *MenuModel::getLevels() {
    return levels_to_play;
}

void MenuModel::setLevels(vector<Level *> *levels) {
    this->levels_to_play = levels;
    notify(LEVEL);
}

//void MenuModel::resetPositions() {
//    for (Entry *entry : this->menuDefinition.get()->entries) {
//        for (EntryAnimation *ea : entry->animations->at(HOVER)) {
//            ea->setPosition(0);
//        }
//        for (EntryAnimation *ea : entry->animations->at(ACTIVATE)) {
//            ea->setPosition(0);
//        }
//        for (EntryAnimation *ea : entry->animations->at(OTHER_ACTIVATED)) {
//            ea->setPosition(0);
//        }
//        for (EntryAnimation *ea : entry->animations->at(DEFAULT)) {
//            ea->setPosition(0);
//        }
//
//    }
//}
//
//void MenuModel::playAnimations() {
//    activated_menu = true;
//    fireInvalidationEvent();
//}
//
//bool MenuModel::isActivatedMenu() {
//    return activated_menu;
//}
//
//void MenuModel::setActivatedMenu(bool i) {
//    activated_menu = i;
//}
//
//
void MenuView::draw() {
    uint32_t start = SDL_GetTicks();
    if (!menuModel->isDone()) {

        const vector<Entry *> &entries = menuModel->getMenuDefinition()->entries;

        vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden
        int i = 1;
//        animationsFinished = true;
        if (!entries.empty()) {
            for (Entry *entry: entries) {
                commands.push_back(drawEntry(entry, 0, i * 200));
                i--;
            }
        }

//        if (this->animationsFinished) {
//            model->setDone(true);
//        }


        //events registreren
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    key_press = event.key.keysym.sym;
                    notify(INPUT);
            }
        }

        //tekenen
        graphics_begin_draw(fontManager->graphics);
        for (vector<GlyphDrawCommand> vec : commands) {
            vector<GlyphDrawCommand>::iterator i = vec.begin();
            while (i != vec.end()) {
                this->fontManager->draw(*i);
                i++;
            }
        }
        graphics_end_draw(fontManager->graphics);

        menuModel->setTime(SDL_GetTicks());
    }

    uint32_t end = SDL_GetTicks();
    menuModel->setTime(menuModel->getTime() + (end - start));
}

void MenuView::invalidated() {
    while (!menuModel->isDone()) {
        this->draw();
    }
}

vector<GlyphDrawCommand>
MenuView::drawEntry(Entry *entry, int x_offset, int y_offset) {
    FontManager *m = this->fontManager;

    // Font, kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
    m->setFont(entry->font); // indien niet gebruikt laatst ingelezen font als font
    m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
    m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

    // Vector met glyphdrawcommands aanmaken
    vector<GlyphDrawCommand> command = m->makeGlyphDrawCommands(entry->long_text, x_offset, y_offset);

//    if (model->isActivatedMenu()) {
//        bool done = true;
//        if (entry == this->model->getSelectedEntry()) {
//            for (EntryAnimation *ea : entry->animations->at(ACTIVATE)) {
//                command = ea->getAnimation()->applyTransform(command, ea->getPosition(nullptr));
//                ea->setPosition(getPosition(time, ea));
//                done &= ea->getPosition(nullptr) == 1;
//            }
//        } else {
//            for (EntryAnimation *ea : entry->animations->at(OTHER_ACTIVATED)) {
//                command = ea->getAnimation()->applyTransform(command, ea->getPosition(nullptr));
//                ea->setPosition(getPosition(time, ea));
//                done &= ea->getPosition(nullptr) == 1;
//            }
//        }
//        this->animationsFinished &= done;
//    } else {
    if (entry == menuModel->getSelectedEntry()) {
        //de hover animaties oproepen
        return applyAnimations(entry->animations->at(HOVER), command);
    } else {
        //de default
        return applyAnimations(entry->animations->at(DEFAULT), command);
    }

//        animationsFinished = false;
//    }
}

vector<GlyphDrawCommand>
MenuView::applyAnimations(vector<EntryAnimation *> animations, vector<GlyphDrawCommand> command) {
    for (EntryAnimation *ea : animations) {
        command = ea->animation->applyTransform(command, ea->getPosition());
        ea->setPosition((float) menuModel->getTime() / (float) ea->duration);
    }
    return command;
}


/**
 * juiste reactie bij de juiste ingedrukte toets
 * @param key de toest die is ingedrukt
 */
void MenuController::onKey(SDLKey key) {
    switch (key) {
        case SDLK_DOWN:
            this->menuModel->down();
            break;
        case SDLK_UP:
            this->menuModel->up();
            break;
        case SDLK_RETURN:
            this->menuModel->select();
            break;
        default:
            break;
    }
}
//
//void MenuController::setMenuModel(MenuModel *model) {
//    this->model = model;
//}
//
//MenuController::~MenuController() {
//
//}
//
//void MenuController::onExitKey() {
//
//}
//
///*
// * berekenen wat de positie moet zijn
// */
//float getPosition(uint64_t time, EntryAnimation *ea) {
//    float position = time / (float) ea->getDuration();
//    if (ea->isRepeat()) {
//        return fmod(position, 1.0f);
//    } else {
//        return position >= 1.0f ? 1.0f : position;
//    }
//}
//
//
/**
 * Starten van de game met de levels die aanwezig zijn
 */
void LevelObserver::notified() {
    if (menuModel != nullptr && !menuModel->getLevels()->empty()) {
        Game *game = game_alloc(graphics);

        Level *level = menuModel->getLevels()->back();
        game_load_level(game, level);
        menuModel->getLevels()->pop_back();
        game->engine.context.current_level = level;
        game->engine.context.is_exit_game = 0;

        Uint32 start_time_ms = SDL_GetTicks();
        Uint32 last_print_time_ms = start_time_ms;
        long update_count = 0;

        while (!game->engine.context.is_exit_game) {
            Uint32 cur_time_ms = SDL_GetTicks();
            Uint32 diff_time_ms = cur_time_ms - last_print_time_ms;

            engine_update(&game->engine);
            update_count++;

            game->engine.context.is_exit_game = game->engine.context.level_ended && menuModel->getLevels()->empty();

            //kijken of er een nieuw level geladen moet worden
            if (!game->engine.context.is_exit_game && game->engine.context.level_ended) {
                if (menuModel->getLevels()->empty()) {
                    game->engine.context.is_exit_game = 1;
                    menuModel->setDone(false);
                }
                Level *next = menuModel->getLevels()->back();
                menuModel->getLevels()->pop_back();
                clear_level(game);
                game_load_level(game, next);
                game->engine.context.current_level = next;
                game->engine.context.level_ended = 0;

            }
            //print performance statistics each second
            if (diff_time_ms > 1000) {
                float time_ms_per_update = (float) diff_time_ms / (float) update_count;
                float fps = 1.0f / time_ms_per_update * 1000.0f;
                game->engine.context.fps = fps;
                last_print_time_ms = cur_time_ms;
                update_count = 0;
            }
        }

#ifdef RPI
        clear_ledgrid();
#endif // RPI

        game_free(game);
        free(game);
    }
}

//LevelObserver::LevelObserver() {
//    //init the graphics system
//    Graphics *graphics = graphics_alloc(0, 0);
//    this->graphics = graphics;
//}
//
//LevelObserver::~LevelObserver() {
//    graphics_free(graphics);
//    free(graphics);
//}
//
//void LevelObserver::setMenuModel(MenuModel *menuModel) {
//    this->menuModel = menuModel;
//    setSubject(menuModel);
//}


void MenuShower::clear() {
    delete mm;
    delete mv;
    delete mc;
}


void MenuShower::show(shared_ptr<MenuDefinition> menuDefinition) {

    mm = new MenuModel;
    mv = new MenuView;
    mc = new MenuController;


    mm->addListener(mv);
    mv->setMenuModel(mm);

    mc->setMenuModel(mm);
    mc->setMenuView(mv);

    mv->setFontManager(fontManager);

    mc->setMenuView(mv);
    mv->registerObserver(INPUT, mc);

    mm->setMenuDefinition(menuDefinition);
}

MenuShower::~MenuShower() {
    clear();
}


void MenuView::setMenuModel(MenuModel *menuModel) {
    this->menuModel = menuModel;
}

SDLKey MenuView::getKey_press() {
    return key_press;
}

void MenuView::setFontManager(FontManager *fontManager) {
    UIView::setFontManager(fontManager);
    LevelObserver *levelObserver = new LevelObserver(fontManager->graphics, menuModel);
    menuModel->registerObserver(LEVEL, levelObserver);
}

void MenuController::setMenuModel(MenuModel *menuModel) {
    this->menuModel = menuModel;
}

void MenuController::setMenuView(MenuView *menuView) {
    this->menuView = menuView;
}

void MenuController::notified() {
    onKey(menuView->getKey_press());
}

