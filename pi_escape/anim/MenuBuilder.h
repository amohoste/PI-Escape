#ifndef PIESCAPE2_MENUBUILDER_H
#define PIESCAPE2_MENUBUILDER_H

#include "Animation.h"
#include "Menu.h"

enum MenuState {
    ACTIVATE, OTHER_ACTIVATED, HOVER, DEFAULT
};

class Menu;

class EntryBuilder {
private:
    bool enabled_on_pc;
    bool enabled_on_pi;
    const char *long_text;
    const char *short_text;
    const char *font;
    char mnemonic;
    const char *action;
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

class MenuBuilder {
public:
    EntryBuilder &addEntry();

    MenuDefinition *build();
};

#endif //PIESCAPE2_MENUBUILDER_H
