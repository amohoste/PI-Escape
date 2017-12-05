#include "Menu.h"
#include "MenuBuilder.h"

#include <utility>
#include <assert.h>

using namespace std;

MenuDefinition::MenuDefinition(deque<Entry *> entries) : entries(std::move(entries)) {

}

MenuDefinition::~MenuDefinition() {
    //entries
    //listeners
}

void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition = std::move(menuDefinition);
    this->selectedInt = 0;
    this->updateSelected();
    this->fireInvalidationEvent();
}

void MenuModel::setTime(uint64_t time) {
    this->time = time;
    fireInvalidationEvent();
}

int MenuModel::isDone() const {
    return done;
}

MenuModel::MenuModel() {
    time = 0;
    done = 0;
    activated_menu = false;
}











shared_ptr<MenuDefinition> MenuModel::getMenuDefinition() {
    return this->menuDefinition;
}

void MenuModel::setDone(int i) {
    this->done = i;
    resetPositions();
    this->time = 0;
    activated_menu = false;
    fireInvalidationEvent();
}

void MenuModel::up() {
    selectedInt = selectedInt == 0 ? 0 : selectedInt - 1;
    this->updateSelected();
    fireInvalidationEvent();
}

void MenuModel::down() {
    selectedInt = selectedInt == this->menuDefinition.get()->entries.size() - 1 ? selectedInt : selectedInt + 1;
    this->updateSelected();
    fireInvalidationEvent();
}

void MenuModel::select() {
    selected->function(this);
}

Entry *MenuModel::getSelectedEntry() {
    return selected;
}

void MenuModel::updateSelected() {
    notify(SELECTION);
    this->selected = this->menuDefinition.get()->entries[this->menuDefinition.get()->entries.size() - 1 -
                                                         this->selectedInt];
}

vector<Level *> *MenuModel::getLevels() {
    return levels;
}

void MenuModel::setLevels(vector<Level *> *levels) {
    this->levels = levels;
    notify(LEVEL);
}

void MenuModel::resetPositions() {
    for (Entry *entry : this->menuDefinition.get()->entries) {
        for (EntryAnimation *ea : entry->animations->at(HOVER)) {
            ea->setPosition(0);
        }
        for (EntryAnimation *ea : entry->animations->at(ACTIVATE)) {
            ea->setPosition(0);
        }
        for (EntryAnimation *ea : entry->animations->at(OTHER_ACTIVATED)) {
            ea->setPosition(0);
        }
        for (EntryAnimation *ea : entry->animations->at(DEFAULT)) {
            ea->setPosition(0);
        }

    }
}

void MenuModel::playAnimations() {
    activated_menu = true;
    fireInvalidationEvent();
}

bool MenuModel::isActivatedMenu() {
    return activated_menu;
}

void MenuModel::setActivatedMenu(bool i) {
    activated_menu = i;
}


void MenuView::draw() {
    last_update = SDL_GetTicks();
    if (!model->isDone()) {
        Uint32 start_time_ms = SDL_GetTicks();

        const deque<Entry *> &entries = this->model->getMenuDefinition()->entries;
        vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden
        int i = -1;
        this->animationsFinished = true;
        if (!entries.empty()) {
            for (Entry *entry: entries) {
                commands.push_back(drawEntry(entry, 0, i * 300, model->getTime()));
                i++;
            }
        }

        if (this->animationsFinished) {
            model->setDone(true);
        }


        //events registreren
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    this->controller->onKey(event.key.keysym.sym);

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

        Uint32 cur_time_ms = SDL_GetTicks();

        model->setTime(model->getTime() + (cur_time_ms - start_time_ms) + (start_time_ms - last_update));

        last_update = SDL_GetTicks();
    }
}

void MenuView::invalidated() {
    this->draw();
}

void MenuView::setModel(MenuModel *model) {
    this->model = model;
}

MenuView::MenuView() {

}

vector<GlyphDrawCommand>
MenuView::drawEntry(Entry *entry, int x_offset, int y_offset, uint64_t time) {
    FontManager *m = this->fontManager;

    // Font, kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
    m->setFont(entry->font); // indien niet gebruikt laatst ingelezen font als font
    m->setColor(0.4f, 0.4f, 0.4f, 1.0f); // Default { 1.0f, 0.0f, 0.0f, 1.0f }
    m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
    m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

    // Vector met glyphdrawcommands aanmaken
    vector<GlyphDrawCommand> command = m->makeGlyphDrawCommands(entry->long_text, x_offset, y_offset);

    if (model->isActivatedMenu()) {
        bool done = true;
        if (entry == this->model->getSelectedEntry()) {
            for (EntryAnimation *ea : entry->animations->at(ACTIVATE)) {
                command = ea->getAnimation()->applyTransform(command, ea->getPosition());
                ea->setPosition(getPosition(time, ea));
                done &= ea->getPosition() == 1;
            }
        } else {
            for (EntryAnimation *ea : entry->animations->at(OTHER_ACTIVATED)) {
                command = ea->getAnimation()->applyTransform(command, ea->getPosition());
                ea->setPosition(getPosition(time, ea));
                done &= ea->getPosition() == 1;
            }
        }
        this->animationsFinished &= done;
    } else {
        if (entry == this->model->getSelectedEntry()) {
            //de hover animaties oproepen
            for (EntryAnimation *ea : entry->animations->at(HOVER)) {
                command = ea->getAnimation()->applyTransform(command, ea->getPosition());
                ea->setPosition(getPosition(time, ea));
            }
        } else {
            //de default
            for (EntryAnimation *ea : entry->animations->at(DEFAULT)) {
                command = ea->getAnimation()->applyTransform(command, ea->getPosition());
                ea->setPosition(getPosition(time, ea));


            }
        }

        animationsFinished = false;

    }

    return command;

}


void MenuView::setController(MenuController *pController) {
    this->controller = pController;
}


/**
 * juiste reactie bij de juiste ingedrukte toets
 * @param key de toest die is ingedrukt
 */
void MenuController::onKey(SDLKey key) {
    switch (key) {
        case SDLK_DOWN:
            this->model->down();
            break;
        case SDLK_UP:
            this->model->up();
            break;
        case SDLK_RETURN:
            this->model->select();
            break;
        default:
            break;
    }
}

void MenuController::setMenuModel(MenuModel *model) {
    this->model = model;
}

MenuController::~MenuController() {

}

void MenuController::onExitKey() {

}

/*
 * berekenen wat de positie moet zijn
 */
float getPosition(uint64_t time, EntryAnimation *ea) {
    float position = time / (float) ea->getDuration();
    if (ea->isRepeat()) {
        return fmod(position, 1.0f);
    } else {
        return position >= 1.0f ? 1.0f : position;
    }
}


/**
 * Starten van de game met de levels die aanwezig zijn
 */
void LevelObserver::notified() {
    if (menuModel != nullptr && !menuModel->getLevels()->empty()) {
        Game *game = game_alloc(graphics);
        this->game = game;

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


            engine_update(&game->engine);
            //kijken of er een nieuw level geladen moet worden
            if (game->engine.context.level_ended) {
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

LevelObserver::LevelObserver() {
    //init the graphics system
    Graphics *graphics = graphics_alloc(0, 0);
    this->graphics = graphics;
}

LevelObserver::~LevelObserver() {
    graphics_free(graphics);
    free(graphics);
}

void LevelObserver::setMenuModel(MenuModel *menuModel) {
    this->menuModel = menuModel;
    setSubject(menuModel);
}
