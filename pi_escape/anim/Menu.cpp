#include "Menu.h"

#include <utility>

using namespace std;

//TODO
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
    done = 1;
}

void MenuModel::addListener(MenuView *view) {
    this->listeners.push_back(view);
}

void MenuModel::fireInvalidationEvent() {
    for (unsigned int i = 0; i < this->listeners.size(); i++) {
        this->listeners[i]->invalidated();
    }
}

shared_ptr<MenuDefinition> MenuModel::getMenuDefinition() {
    return this->menuDefinition;
}

void MenuModel::setDone(int i) {
    this->done = i;
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
    this->selected = this->menuDefinition.get()->entries[this->menuDefinition.get()->entries.size() - 1 -
                                                         this->selectedInt];
}

deque<Level *> *MenuModel::getLevels() {
    return levels;
}

void MenuModel::setLevels(deque<Level *> *levels) {
    this->levels = levels;
    notify(LEVEL);
}


void MenuView::draw() {
    const deque<Entry *> &entries = this->model->getMenuDefinition()->entries;
    vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden
    int i = -1;
    if (!entries.empty()) {
        for (Entry *entry: entries) {
            commands.push_back(drawEntry(entry, 0, i * 300, model->getTime()));
            i++;
        }
    }

    while (this->model->isDone()) {
        Uint32 start_time_ms = SDL_GetTicks();

        //events registreren
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    this->controller->onKey(event.key.keysym.sym);

            }
        }

        //tekenen
        graphics_begin_draw(graphics);
        for (vector<GlyphDrawCommand> vec : commands) {
            vector<GlyphDrawCommand>::iterator i = vec.begin();
            while (i != vec.end()) {
                this->fontManager->draw(*i);
                i++;
            }
        }
        graphics_end_draw(graphics);

        Uint32 cur_time_ms = SDL_GetTicks();

        model->setTime(model->getTime() + (cur_time_ms - start_time_ms));
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

    if (entry == this->model->getSelectedEntry()) {
        //de hover animaties oproepen
        for (EntryAnimation *ea : entry->animations_hover) {
            command = ea->getAnimation()->applyTransform(command, getPosition(time, ea->getDuration()));
        }
    } else {
        //de default
        for (EntryAnimation *ea : entry->animations_default) {
            command = ea->getAnimation()->applyTransform(command, getPosition(time, ea->getDuration()));
        }
    }

    return command;

}

void MenuView::setFontManager(FontManager *fm) { this->fontManager = fm; }

void MenuView::setGraphics(Graphics *graphics) {
    this->graphics = graphics;
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

float getPosition(uint64_t time, long duration) {
    return (time % duration) / (float) duration;
}


void LevelObserver::notified() {
   cout << "hallo door deze functie moet de game starten" << endl;

//
//    //init the graphics system
//    Graphics *graphics = graphics_alloc(0, 0);
//
//    //initialise context, engine and assemblage, and add systems
//    Game *pi_escape_2 = game_alloc(graphics);
//
//    //een level inladen kan je doen door gewoon op te  geven het hoeveelste level het is -> beginnend vanaf 1
//    //vanaf level 7 worden de echte games geladen en niet de tutorials
//    Level *level = load_level(1);
//    game_load_level(pi_escape_2, level);
//
//
//
//
//    while (!pi_escape_2->engine.context.is_exit_game) {
//        engine_update(&pi_escape_2->engine);
//
//        //kijken of er een nieuw level geladen moet worden
//        if (pi_escape_2->engine.context.level_ended) {
//
//
//            int new_level_nr = pi_escape_2->engine.context.current_level->nr + 1;
//            if (new_level_nr > 10) {
//                pi_escape_2->engine.context.is_exit_game = 1;
//            } else {
//                Level *next = load_level(new_level_nr);
//                clear_level(pi_escape_2);
//                game_load_level(pi_escape_2, next);
//                pi_escape_2->engine.context.current_level = next;
//                pi_escape_2->engine.context.level_ended = 0;
//            }
//        }
//
//
//    }
//
//    game_free(pi_escape_2);
//    free(pi_escape_2);
//
//    graphics_free(graphics);
//    free(graphics);

}
