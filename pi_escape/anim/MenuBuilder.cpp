#include "MenuBuilder.h"

using namespace std;


EntryBuilder &MenuBuilder::getEntryBuilder() {
    EntryBuilder *eb = new EntryBuilder();
    eb->setMenuBuilder(this); //zodat we later een referentie hebben voor de entries
    EntryBuilder &ref = *eb;
    return ref;
}

MenuDefinition *MenuBuilder::build() {
    return nullptr;
}

void addEntry(MenuBuilder *mb, Entry *entry) {
    mb->entries.push_back(entry);
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
    addEntry(this->menuBuilder, new Entry());
    return *this;
}

void EntryBuilder::setMenuBuilder(MenuBuilder *menuBuilder) {
    this->menuBuilder = menuBuilder
}

Entry::Entry(bool enabled_on_pc, bool enabled_on_pi, const char *long_text,
             const char *short_text, char mnemonic, const char *action, bool repeat, long duration,
             MenuState menuState, Animation animation) : duration(duration), enabled_on_pc(enabled_on_pc),
                                                         enabled_on_pi(enabled_on_pi), long_text(long_text),
                                                         short_text(short_text), mnemonic(mnemonic), action(action),
                                                         repeat(repeat) {

}
