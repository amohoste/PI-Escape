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
    //todo
//    addEntry(this->menuBuilder,
//             new Entry(this->enabled_on_pc, this->enabled_on_pi, this->long_text, this->short_text, this->mnemonic,
//                       this->action, this->font, &animations, function));
    return *this;
}


EntryBuilder::EntryBuilder() {
    animations[ACTIVATE].clear();
    animations[OTHER_ACTIVATED].clear();
    animations[HOVER].clear();
    animations[DEFAULT].clear();

}


//EntryAnimation::EntryAnimation(Animation *animation, MenuState menuState, bool repeat, long duration) : animation(
//        animation), menuState(menuState), duration(duration), repeat(repeat) {
//
//}
//
//Animation const *EntryAnimation::getAnimation() {
//    return animation;
//}
//
//const long EntryAnimation::getDuration() {
//    return duration;
//}
//
//bool EntryAnimation::isRepeat() {
//    return repeat;
//}
//
//float EntryAnimation::getPosition(Animation *pAnimation) {
//    return position;
//}
//
//void EntryAnimation::setPosition(float x) {
//    this->position = x;
//}
//
//Entry::Entry(bool enabled_on_pc, bool enabled_on_pi, const char *long_text, const char *short_text, char mnemonic,
//             const char *action, const char *font,
//             map<MenuState, vector<EntryAnimation *>> *animations,
//             func_t function) : enabled_on_pi(
//        enabled_on_pi),
//                                enabled_on_pc(
//                                        enabled_on_pc),
//                                long_text(long_text),
//                                short_text(short_text),
//                                mnemonic(mnemonic),
//                                action(action),
//                                font(font),
//                                animations(animations),
//                                function(function) {
//
//}
