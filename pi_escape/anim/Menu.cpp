#include "Menu.h"
#include "MenuBuilder.h"

#include <utility>
#include <assert.h>
#include <functional>

using namespace std;


void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition.reset(); //niet deleten maar resetten
    this->menuDefinition = std::move(menuDefinition);

    selectedInt = 0;
    time = 0;
    done = false;
    activated_menu = false;

    levels_to_play.clear();

    notify(SELECTION);

    while (!done || activated_menu) {
        fireInvalidationEvent();
    }
}

shared_ptr<MenuDefinition> MenuModel::getMenuDefinition() {
    return this->menuDefinition;
}


Entry *MenuModel::getSelectedEntry() {
    return getMenuDefinition().get()->entries[selectedInt];
}

vector<Level *> *MenuModel::getLevels() {
    return &levels_to_play;
}

void MenuModel::setLevels(vector<Level *> levels) {
    this->levels_to_play = std::move(levels);
}

bool MenuModel::isActivated() {
    return activated_menu;
}

void MenuModel::setActivated(bool i) {
    activated_menu = i;
}

void MenuModel::selectFunction() {
    fireInvalidationEvent();
    getSelectedEntry()->function(this);
}

void MenuModel::reset_start_times() {

    std::function<void(MenuState ms)> f = [this](MenuState ms) {
        for (Entry *entry: this->menuDefinition.get()->entries) {
            for (EntryAnimation *ea : entry->animations->at(ms)) {
                ea->setStartTime(getTime());
            }
        }
    };

    f(HOVER);
    f(ACTIVATE);
    f(OTHER_ACTIVATED);
    f(DEFAULT);
}

vector<shared_ptr<MovieDefinition>> *MenuModel::getMovieDefinitions() {
    return movieDefinitions;
}

MenuModel::MenuModel() {

}

MenuModel::~MenuModel() {
    menuDefinition.reset();

    for (std::vector<shared_ptr<MovieDefinition>>::iterator it = movieDefinitions->begin();
         it != movieDefinitions->end(); ++it) {
        it->reset();
    }
    delete movieDefinitions;
}

void MenuModel::incrementSelectedInt(int i) {
    selectedInt += i;
    int size = (int) this->menuDefinition.get()->entries.size();
    selectedInt =
            selectedInt >= size ? size - 1
                                      : selectedInt;
    selectedInt = selectedInt < 0 ? 0 : selectedInt;
    fireInvalidationEvent();
    notify(SELECTION);

}


void MenuView::draw() {
    uint32_t start = SDL_GetTicks();
    if (!menuModel->isDone() || menuModel->isActivated()) {

        const vector<Entry *> &entries = menuModel->getMenuDefinition().get()->entries;

        //kleur instellen voor alles
        glmc_assign_vec3(fontManager->graphics->background_color, *menuModel->getMenuDefinition().get()->color);

        vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden
        uint32_t height = fontManager->graphics->height;
        int i = (int) ceil(entries.size()/2);
        int offset = static_cast<int>( height / (entries.size() + 2));
        if (!entries.empty()) {
            for (Entry *entry: entries) {
                commands.push_back(drawEntry(entry, 0, i *offset));
                i--;
            }
        }

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
        fontManager->begin_draw();
        for (vector<GlyphDrawCommand> vec : commands) {
            vector<GlyphDrawCommand>::iterator i = vec.begin();
            while (i != vec.end()) {
                this->fontManager->draw(*i);
                i++;
            }
        }
        fontManager->end_draw();

        menuModel->setTime(SDL_GetTicks());
    }

    uint32_t end = SDL_GetTicks();
    menuModel->setTime(menuModel->getTime() + (end - start));
}

void MenuView::invalidated() {
    while (!menuModel->getMovieDefinitions()->empty() && !menuModel->isActivated()) {
        menuModel->setDone(true);
        cout << menuModel->getLevels()->size() << endl;
        moviePlayer->play(menuModel->getMovieDefinitions()->back());
        menuModel->getMovieDefinitions()->pop_back();
        menuModel->setDone(false);
    }
    this->draw();
    if (!menuModel->getLevels()->empty() && !menuModel->isActivated()) {
        cout << menuModel->getLevels()->size() << endl;
        notify(LEVEL);
        notify(SELECTION); //zodat de pi zijn scherm veranderd
    }
}

vector<GlyphDrawCommand>
MenuView::drawEntry(Entry *entry, int x_offset, int y_offset) {
    FontManager *m = this->fontManager;

    // Font, kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
    m->setFont(entry->font); // indien niet gebruikt laatst ingelezen font als font
    m->setColor(*entry->color);
    m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
    m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

    // Vector met glyphdrawcommands aanmaken
    vector<GlyphDrawCommand> command = m->makeGlyphDrawCommands(entry->long_text, x_offset, y_offset);

    if (menuModel->isActivated()) {
        menuModel->setActivated(false); //in de applyAnimations wordt gekeken of hij activated moet blijven
        if (entry == menuModel->getSelectedEntry()) {
            return applyAnimations(entry->animations->at(ACTIVATE), command);
        } else {
            return applyAnimations(entry->animations->at(OTHER_ACTIVATED), command);
        }

    } else {
        //hier telkens de activated zeker op false zetten
        //niet zo mooi, beetje een hack maarja het werkt
        if (entry == menuModel->getSelectedEntry()) {
            //de hover animaties oproepen
            const vector<GlyphDrawCommand> &vector = applyAnimations(entry->animations->at(HOVER), command);
            menuModel->setActivated(false);
            return vector;
        } else {
            //de default
            const vector<GlyphDrawCommand> &vector = applyAnimations(entry->animations->at(DEFAULT), command);
            menuModel->setActivated(false);
            return vector;
        }
    }
}

vector<GlyphDrawCommand>
MenuView::applyAnimations(vector<EntryAnimation *> animations, vector<GlyphDrawCommand> command) {
    for (EntryAnimation *ea : animations) {
        command = ea->animation->applyTransform(command, ea->getPosition());
        ea->setPosition(((float) menuModel->getTime() - (float) ea->getStartTime()) / (float) ea->duration);
        menuModel->setActivated(menuModel->isActivated() || ea->getPosition() < 1);
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
            down();
            break;
        case SDLK_UP:
            up();
            break;
        case SDLK_RETURN:
            select();
            break;
        default:
            break;
    }
}

void MenuController::up() {
    menuModel->incrementSelectedInt(-1);
}

void MenuController::down() {
    menuModel->incrementSelectedInt(1);
}

void MenuController::select() {
    menuModel->setActivated(true);
    menuModel->setDone(true);
    menuModel->reset_start_times();
    menuModel->selectFunction();


}

/**
 * Starten van de game met de levels die aanwezig zijn
 */
void LevelObserver::notified() {
    if (menuModel != nullptr && !menuModel->getLevels()->empty()) {
        Game *game = game_alloc(graphics);

        Level *level = menuModel->getLevels()->back();
        game_load_level(game, level);
        game->engine.context.current_level = level;
        game->engine.context.is_exit_game = 0;

        Uint32 start_time_ms = SDL_GetTicks();
        Uint32 last_print_time_ms = start_time_ms;
        long update_count = 0;

        while (!game->engine.context.is_exit_game) {
            Uint32 cur_time_ms = SDL_GetTicks();
            Uint32 diff_time_ms = cur_time_ms - last_print_time_ms;

            game->engine.context.is_exit_game = game->engine.context.level_ended && menuModel->getLevels()->empty();

            engine_update(&game->engine);
            update_count++;


            //kijken of er een nieuw level geladen moet worden
            if (!game->engine.context.is_exit_game && game->engine.context.level_ended) {
                menuModel->getLevels()->pop_back();
                if (menuModel->getLevels()->empty()) {
                    game->engine.context.is_exit_game = 1;
                    menuModel->setDone(false);
                } else {
                    Level *next = menuModel->getLevels()->back();
                    clear_level(game);
                    game_load_level(game, next);
                    game->engine.context.current_level = next;
                    game->engine.context.level_ended = 0;
                }

            }
            //print performance statistics each second
            if (diff_time_ms > 1000) {
                float time_ms_per_update = (float) diff_time_ms / (float) update_count;
                float fps = 1.0f / time_ms_per_update * 1000.0f;
                game->engine.context.fps = fps;
                cout << fps << endl;
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
//    eventueel animaties verwijderen als je stout bent geweest en op escape hebt gedrukt...
    if (!menuModel->getLevels()->empty()) {
        menuModel->getMovieDefinitions()->clear();
    }

    menuModel->getLevels()->clear();
    menuModel->setDone(false);
}

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

    mm->setMenuDefinition(std::move(menuDefinition));
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
    registerObserver(LEVEL, levelObserver);

    moviePlayer = new MoviePlayer(fontManager);
}

MenuView::~MenuView() {
    delete moviePlayer;
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


MenuDefinition::~MenuDefinition() {
    delete[] color;

    for (Entry *entry: entries) {
        delete (entry);
    }
}
