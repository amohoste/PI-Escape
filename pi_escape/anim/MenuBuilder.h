#ifndef PIESCAPE2_MENUBUILDER_H
#define PIESCAPE2_MENUBUILDER_H

#include <deque>
#include <list>
#include "Animation.h"
#include "Menu.h"

enum MenuState {
    ACTIVATE, OTHER_ACTIVATED, HOVER, DEFAULT
};

class Menu;

class MenuDefinition;

class MenuBuilder;

class EntryAnimation;

class MenuModel;

using func_t = std::add_pointer<void(MenuModel *)>::type;

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
    func_t function;
    vector<EntryAnimation *> animations_active;
    vector<EntryAnimation *> animations_other;
    vector<EntryAnimation *> animations_hover;
    vector<EntryAnimation *> animations_default;
public:

    EntryBuilder &addAnimation(Animation *animation, MenuState activate, bool repeat, long duration);

    EntryBuilder &setEnabledOnPc(bool b);

    EntryBuilder &setEnabledOnPi(bool b);

    EntryBuilder &setLongText(const char *text);

    EntryBuilder &setShortText(const char *text);

    EntryBuilder &setFontName(const char *text);

    EntryBuilder &setMnemonic(char c);

    EntryBuilder &buildEntryWithAction(const char *action);

    EntryBuilder &setFunction(func_t function);

    void setMenuBuilder(MenuBuilder *menuBuilder);

};

class EntryAnimation {
private:
    const Animation *animation;
    const MenuState menuState;
    const long duration;
    const bool repeat;
public:
    EntryAnimation(Animation *animation, MenuState menuState, bool repeat, long duration);

    const Animation *getAnimation();

    const long getDuration();
};

class Entry {
public:
    const bool enabled_on_pi;
    const bool enabled_on_pc;
    const char *long_text;
    const char *short_text;
    const char mnemonic;
    const char *action;
    const char *font;
    const vector<EntryAnimation *> animations_active;
    const vector<EntryAnimation *> animations_other;
    const vector<EntryAnimation *> animations_hover;
    const vector<EntryAnimation *> animations_default;
    const func_t function;

    Entry(bool enabled_on_pc, bool enabled_on_pi, const char *long_text,
          const char *short_text, char mnemonic, const char *action, const char *font,
          const vector<EntryAnimation *> &animations_active, const vector<EntryAnimation *> &animations_other,
          const vector<EntryAnimation *> &animations_hover, const vector<EntryAnimation *> &animations_default,
          func_t function);
};

class MenuBuilder {
private:
    std::deque<Entry *> entries;
public:
    EntryBuilder &getEntryBuilder();

    MenuDefinition *build();

    friend void addEntry(MenuBuilder *mb, Entry *entry);
};

float getPosition(uint64_t time, long duration);

#endif //PIESCAPE2_MENUBUILDER_H
