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
    if (!entries.empty()) {
        for(Entry* entry: entries){
            this->drawItem(entry);
        }
    }
}

void MenuView::invalidated() {
    cout << "I am invalidated" << endl;
    this->draw();
}

void MenuView::setModel(MenuModel *model) {
    this->model = model;
}

MenuView::MenuView() {
}

void MenuView::drawItem(Entry *entry) {
    FontManager* m = this->fontManager;

	// Font, kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
	m->setFont("zorque"); // indien niet gebruikt laatst ingelezen font als font
	m->setColor(0.4f, 0.4f, 0.4f, 1.0f); // Default { 1.0f, 0.0f, 0.0f, 1.0f }
	m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
	m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

	// Vector met glyphdrawcommands aanmaken
	vector<GlyphDrawCommand> result = m->makeGlyphDrawCommands(entry->long_text, 0, 0);

        //this is a demo of gl_glyph_draw
    Uint32 start_time_ms = SDL_GetTicks();
    Uint32 diff_time_ms = 0;

    t_vec4 col = { 1.0f, 0.0f, 0.0f, 1.0f };

    while (diff_time_ms < 500) {
        graphics_begin_draw(m->graphics);

        glmc_vec4_set(col, diff_time_ms / 5000.0f, 0.0f, 0.0f, 1.0f);

		// Glyphdrawcommands tekenen en als kleur col nemen
		vector<GlyphDrawCommand>::iterator i = result.begin();
		while (i != result.end()) {
			m->draw((*i).changeColor(col));
			i++;
		}

        graphics_end_draw(m->graphics);

        Uint32 cur_time_ms = SDL_GetTicks();
        diff_time_ms = cur_time_ms - start_time_ms;
    }
}

void MenuView::setFontManager(FontManager *fm) {
    this->fontManager = fm;
}

