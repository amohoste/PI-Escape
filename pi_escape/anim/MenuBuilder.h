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
    MenuBuilder *menuBuilder;
    bool enabled_on_pc;
    bool enabled_on_pi;
    const char *long_text;
    const char *short_text;
    const char *font;
    char mnemonic;
    const char *action;
    bool repeat;
    long duration;
    MenuState menuState;
    Animation *animation;
public:
    EntryBuilder &addAnimation(Animation *animation, MenuState activate, bool repeat, long duration);

    EntryBuilder &setEnabledOnPc(bool b);

    EntryBuilder &setEnabledOnPi(bool b);

    EntryBuilder &setLongText(const char *text);

    EntryBuilder &setShortText(const char *text);

    EntryBuilder &setFontName(const char *text);

    EntryBuilder &setMnemonic(char c);

    EntryBuilder &buildEntryWithAction(const char *action);

    void setMenuBuilder(MenuBuilder *menuBuilder);

};

class Entry {
public:
    const bool enabled_on_pc;
    const bool enabled_on_pi;
    const char *long_text;
    const char *short_text;
    const char *font;
    const char mnemonic;
    const const char *action;
    const bool repeat;
    const long duration;
    const MenuState menuState;
    const Animation *animation;

    Entry(bool enabled_on_pc, bool enabled_on_pi, const char *long_text,
          const char *short_text, char mnemonic, const char *action, bool repeat, long duration, MenuState menuState, Animation animation);
};

class MenuBuilder {
private:
    vector<Entry *> entries;
public:
    EntryBuilder &getEntryBuilder();

    MenuDefinition *build();

    friend void addEntry(MenuBuilder *mb, Entry *entry);
};

#endif //PIESCAPE2_MENUBUILDER_H
