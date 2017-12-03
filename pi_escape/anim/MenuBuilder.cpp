#include "MenuBuilder.h"

using namespace std;


EntryBuilder &MenuBuilder::getEntryBuilder() {
    EntryBuilder *eb = new EntryBuilder();
    eb->setMenuBuilder(this); //zodat we later een referentie hebben voor de entries
    EntryBuilder &ref = *eb;
    return ref;
}

MenuDefinition *MenuBuilder::build() {
    return new MenuDefinition(this->entries);
}

void addEntry(MenuBuilder *mb, Entry *entry) {
    mb->entries.push_front(entry);
}


EntryBuilder &EntryBuilder::addAnimation(Animation *animation, MenuState activate, bool repeat, long duration) {
    EntryAnimation *ea = new EntryAnimation(animation, activate, repeat, duration);
    switch (activate) {
        case ACTIVATE:
            animations_active.push_back(ea);
        case HOVER:
            animations_hover.push_back(ea);
        case OTHER_ACTIVATED:
            animations_other.push_back(ea);
        case DEFAULT:
            animations_default.push_back(ea);
    }
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
    addEntry(this->menuBuilder,
             new Entry(this->enabled_on_pc, this->enabled_on_pi, this->long_text, this->short_text, this->mnemonic,
                       this->action, this->font, this->animations_active, animations_other, animations_hover,
                       animations_default, function));
    return *this;
}

void EntryBuilder::setMenuBuilder(MenuBuilder *menuBuilder) {
    this->menuBuilder = menuBuilder;
}

EntryBuilder &EntryBuilder::setFunction(func_t function) {
    this->function = function;
    return *this;
}


EntryAnimation::EntryAnimation(Animation *animation, MenuState menuState, bool repeat, long duration) : animation(
        animation), menuState(menuState), duration(duration), repeat(repeat) {

}

Animation const *EntryAnimation::getAnimation() {
    return animation;
}

const long EntryAnimation::getDuration() {
    return duration;
}

Entry::Entry(bool enabled_on_pc, bool enabled_on_pi, const char *long_text, const char *short_text, char mnemonic,
             const char *action, const char *font, const vector<EntryAnimation *> &animations_active,
             const vector<EntryAnimation *> &animations_other, const vector<EntryAnimation *> &animations_hover,
             const vector<EntryAnimation *> &animations_default, func_t function) : enabled_on_pi(
        enabled_on_pi),
                                                                                    enabled_on_pc(
                                                                                            enabled_on_pc),
                                                                                    long_text(long_text),
                                                                                    short_text(short_text),
                                                                                    mnemonic(mnemonic),
                                                                                    action(action),
                                                                                    font(font),
                                                                                    animations_active(
                                                                                            animations_active),
                                                                                    animations_other(animations_other),
                                                                                    animations_hover(animations_hover),
                                                                                    animations_default(
                                                                                            animations_default),
                                                                                    function(function) {

}
