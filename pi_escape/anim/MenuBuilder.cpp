#include "MenuBuilder.h"

using namespace std;


EntryBuilder &MenuBuilder::getEntryBuilder() {
    EntryBuilder *eb = new EntryBuilder();
    eb->setMenuBuilder(this); //zodat we later een referentie hebben voor de entries
    return *eb;
}

MenuDefinition *MenuBuilder::build() {
    return new MenuDefinition(this->entries);
}

void addEntry(MenuBuilder *mb, Entry *entry) {
    mb->entries.push_back(entry);
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

EntryBuilder &EntryBuilder::setFunction(func_t function) {
    this->function = function;
    return *this;
}

void EntryBuilder::setMenuBuilder(MenuBuilder *menuBuilder) {
    this->menuBuilder = menuBuilder;
}

EntryBuilder &EntryBuilder::buildEntryWithAction(const char *action) {
    this->action = action;
    addEntry(this->menuBuilder,
             new Entry(this->enabled_on_pc, this->enabled_on_pi, this->long_text, this->short_text, this->mnemonic,
                       this->action, this->font, &animations, function));
    return *this;
}


EntryBuilder::EntryBuilder() {
    animations[ACTIVATE].clear();
    animations[OTHER_ACTIVATED].clear();
    animations[HOVER].clear();
    animations[DEFAULT].clear();

}

float EntryAnimation::getPosition() {
    return position;
}

void EntryAnimation::setPosition(float x) {
    if (repeat) {
        position = static_cast<float>(fmod(x, 1));
    } else{
        position = x > 1 ? 1 : x;
    }
}

