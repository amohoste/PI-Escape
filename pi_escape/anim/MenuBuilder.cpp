#include "MenuBuilder.h"

using namespace std;


EntryBuilder &MenuBuilder::addEntry() {
    //todo
    EntryBuilder skip;
    return skip;
}

MenuDefinition *MenuBuilder::build() {
    return nullptr;
}


EntryBuilder &EntryBuilder::addAnimation(Animation *animation, MenuState activate, bool repeat, long duration) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::setEnabledOnPc(bool b) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::setEnabledOnPi(bool b) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::setLongText(const char *text) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::setShortText(const char *text) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::setFontName(const char *text) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::setMnemonic(char c) {
    //todo
    return *this;
}

EntryBuilder &EntryBuilder::buildEntryWithAction(const char *action) {
    //todo
    return *this;
}
