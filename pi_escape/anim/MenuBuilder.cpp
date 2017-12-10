#include "MenuBuilder.h"

using namespace std;


EntryBuilder &MenuBuilder::getEntryBuilder() {
    EntryBuilder *eb = new EntryBuilder();
    eb->setMenuBuilder(this); //zodat we later een referentie hebben voor de entries
    return *eb;
}

MenuDefinition *MenuBuilder::build() {
    t_vec3 *background = new t_vec3[3];
    memcpy(background, this->background_color, sizeof(t_vec3));
    return new MenuDefinition(this->entries, background);
}

void addEntry(MenuBuilder *mb, Entry *entry) {
    mb->entries.push_back(entry);
}

void MenuBuilder::setBackGroundColor(t_vec3 color) {
    glmc_assign_vec3(this->background_color, color);
}

MenuBuilder::MenuBuilder() {
}


EntryBuilder &EntryBuilder::addAnimation(Animation *animation, MenuState activate, bool repeat, long duration) {
    EntryAnimation *ea = new EntryAnimation(animation, activate, repeat, duration);
    animations[activate].push_back(ea);
    return *this;
}

EntryBuilder &EntryBuilder::setEnabledOnPc(bool b) {
    this->enabled_on_pc = b;
    return *this;
}

EntryBuilder &EntryBuilder::setEnabledOnPi(bool b) {
    this->enabled_on_pi = b;
    return *this;
}

EntryBuilder &EntryBuilder::setLongText(const char *text) {
    this->long_text = text;
    return *this;
}

EntryBuilder &EntryBuilder::setShortText(const char *text) {
    this->short_text = text;
    return *this;
}

EntryBuilder &EntryBuilder::setFontName(const char *text) {
    this->font = text;
    return *this;
}

EntryBuilder &EntryBuilder::setMnemonic(char c) {
    this->mnemonic = c;
    return *this;
}

EntryBuilder &EntryBuilder::setColor(t_vec3 color) {
    glmc_assign_vec4(this->color, color);
    return *this;
}

EntryBuilder &EntryBuilder::setFunction(func_t function) {
    this->function = function;
    return *this;
}

void EntryBuilder::setMenuBuilder(MenuBuilder *menuBuilder) {
    this->menuBuilder = menuBuilder;
}

EntryBuilder &EntryBuilder::buildEntryWithAction(const char *action) {
    t_vec4 *color = new t_vec4[4];
    memcpy(color, this->color, sizeof(t_vec4));
    this->action = action;
    addEntry(this->menuBuilder,
             new Entry(this->enabled_on_pc, this->enabled_on_pi, this->long_text, this->short_text, this->mnemonic,
                       this->action, this->font, &animations, function, color));
    return *this;
}


EntryBuilder::EntryBuilder() {
    animations[ACTIVATE].clear();
    animations[OTHER_ACTIVATED].clear();
    animations[HOVER].clear();
    animations[DEFAULT].clear();

}

EntryBuilder::~EntryBuilder() {
    map<MenuState, std::vector<EntryAnimation *>>::const_iterator iterator = animations.begin();
    for (iterator; iterator != animations.end(); iterator++) {
        for (EntryAnimation *ea : iterator->second) {
            delete (ea);
        }
    }

}

float EntryAnimation::getPosition() {
    return position;
}

void EntryAnimation::setPosition(float x) {
    if (repeat) {
        position = (fmod(x, 1.0f));
    } else {
        position = x > 1 ? 1 : x;
    }
}

EntryAnimation::~EntryAnimation() {
    delete animation;
}

Entry::~Entry() {

    map<MenuState , vector<EntryAnimation*>>::const_iterator it;

    for (it = animations->begin(); it != animations->end(); it++) {
        for(EntryAnimation* ea : it->second){
            delete(ea);
        }
    }
}
