#include "Menu.h"
#include "MenuBuilder.h"

#include <utility>
#include <assert.h>

using namespace std;


void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition = std::move(menuDefinition);
    selectedInt = 0;
    time = 0;
    done = false;
    activated_menu = false;
    fireInvalidationEvent();
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
    //todo deze shit moet in controller
    activated_menu = true;
    done = true;
    this->reset_start_times();
    fireInvalidationEvent();
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

bool MenuModel::isActivated() {
    return activated_menu;
}

void MenuModel::setActivated(bool i) {
    activated_menu = i;
}

void MenuModel::reset_start_times() {

    auto f = [this](MenuState ms) {
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


void MenuView::draw() {
    uint32_t start = SDL_GetTicks();
    if (!menuModel->isDone() || menuModel->isActivated()) {

        const vector<Entry *> &entries = menuModel->getMenuDefinition().get()->entries;

        //kleur instellen voor alles
        glmc_assign_vec3(fontManager->graphics->background_color, menuModel->getMenuDefinition().get()->color);

        vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden
        int i = 1;
        if (!entries.empty()) {
            for (Entry *entry: entries) {
                commands.push_back(drawEntry(entry, 0, i * 200));
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
    while (!menuModel->isDone() || menuModel->isActivated()) {
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

