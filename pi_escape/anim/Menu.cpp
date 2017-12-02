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
    this->fireInvalidationEvent();
}

void MenuModel::setTime(uint64_t) {
    //todo
}

int MenuModel::isDone() const {
    //todo
    return 0;
}

MenuModel::MenuModel() {

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


void MenuView::draw() {
    const vector<Entry *> &entries = this->model->getMenuDefinition()->entries;
    vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden
    int i = -1;
    if (!entries.empty()) {
        for (Entry *entry: entries) {
            commands.push_back(drawEntry(entry, i* 300,0));
            i++;
        }
    }
    cout << commands.size() << endl;

    t_vec4 col = {1.0f, 0.0f, 0.0f, 1.0f};
    //this is a demo of gl_glyph_draw
    Uint32 start_time_ms = SDL_GetTicks();
    Uint32 diff_time_ms = 0;
    while (diff_time_ms < 5000) {
        graphics_begin_draw(graphics);
        glmc_vec4_set(col, diff_time_ms / 5000.0f, 0.0f, 0.0f, 1.0f);
        for (vector<GlyphDrawCommand> vec : commands) {
            vector<GlyphDrawCommand>::iterator i = vec.begin();
            while (i != vec.end()) {
                this->fontManager->draw((*i).changeColor(col));
                i++;
            }
            graphics_end_draw(graphics);
            Uint32 cur_time_ms = SDL_GetTicks();
            diff_time_ms = cur_time_ms - start_time_ms;
        }
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

vector<GlyphDrawCommand> MenuView::drawEntry(Entry *entry, int x_offset, int y_offset) {
    FontManager *m = this->fontManager;

    // Font, kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
    m->setFont(entry->font); // indien niet gebruikt laatst ingelezen font als font
    m->setColor(0.4f, 0.4f, 0.4f, 1.0f); // Default { 1.0f, 0.0f, 0.0f, 1.0f }
    m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
    m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

    // Vector met glyphdrawcommands aanmaken
    return m->makeGlyphDrawCommands(entry->long_text, y_offset, x_offset);
}

void MenuView::setFontManager(FontManager *fm) { this->fontManager = fm; }

void MenuView::setGraphics(Graphics *graphics) {
    this->graphics = graphics;
}
