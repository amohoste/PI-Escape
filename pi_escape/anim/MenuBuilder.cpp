#include "MenuBuilder.h"

using namespace std;


EntryBuilder &MenuBuilder::addEntry() {
    EntryBuilder *eb = new EntryBuilder();
    entries.push_back(eb);
    EntryBuilder &ref = *eb;
    return ref;
}

MenuDefinition *MenuBuilder::build() {
    return nullptr;
}


EntryBuilder &EntryBuilder::addAnimation(Animation *animation, MenuState activate, bool repeat, long duration) {
    this->repeat = repeat;
    this->duration = duration;
    this->menuState = activate;
    this->animation = animation;
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

EntryBuilder &EntryBuilder::buildEntryWithAction(const char *action) {
    this->action = action;
    return *this;
}
