#include "Menu.h"

#include <utility>

using namespace std;

//TODO
MenuDefinition::MenuDefinition(vector<Entry *> entries) : entries(std::move(entries)) {

}

MenuDefinition::~MenuDefinition() {
    //entries
    //listeners
}

void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition = std::move(menuDefinition);
    this->selected = 0;
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
    for (int i = 0; i < this->listeners.size(); i++) {
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
    selected = selected == 0 ? 0 : selected - 1;
    cout << selected << endl;
    fireInvalidationEvent();
}

void MenuModel::down() {
    selected = selected == this->menuDefinition.get()->entries.size() - 1 ? selected : selected + 1;
    fireInvalidationEvent();
}

void MenuModel::select() {
    done = 0;
}


void MenuView::draw() {
    const vector<Entry *> &entries = this->model->getMenuDefinition()->entries;
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

//    for (EntryAnimation *ea : entry->animations) {
    FadeInAnimation *animation = new FadeInAnimation();
    command = animation->applyTransform(command, getPosition(time, 1000));
//        command = ea->getAnimation()->applyTransform(command, getPosition(time, ea->getDuration()));
//    }

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

