#ifndef PIESCAPE2_MENUBUILDER_H
#define PIESCAPE2_MENUBUILDER_H

#include "Animation.h"
#include "Menu.h"

enum MenuState {
    ACTIVATE, OTHER_ACTIVATED, HOVER, DEFAULT
};

class Menu;

class MenuBuilder {
public:
    EntryBuilder &addEntry();

    MenuDefinition *build();
};

class EntryBuilder {
public:
    EntryBuilder &addAnimation(Animation *animation, MenuState activate, bool repeat, long duration);

    EntryBuilder &setEnabledOnPc(bool b);

    EntryBuilder &setEnabledOnPi(bool b);

    EntryBuilder &setLongText(const char *text);

    EntryBuilder &setShortText(const char *text);

    EntryBuilder &setFontName(const char *text);

    EntryBuilder &setMnemonic(char c);

    EntryBuilder &buildEntryWithAction(const char *action);
};

#endif //PIESCAPE2_MENUBUILDER_H
