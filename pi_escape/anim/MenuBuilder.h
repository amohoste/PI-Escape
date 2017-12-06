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
    std::map<MenuState, std::vector<EntryAnimation *>> animations;
public:
    EntryBuilder();

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
    float position = 0;
public:
    const Animation *animation;
    const MenuState menuState;
    const long duration;
    const bool repeat;

    EntryAnimation(Animation *animation, MenuState menuState, bool repeat, long duration) : animation(animation),
                                                                                            menuState(menuState),
                                                                                            repeat(repeat),
                                                                                            duration(duration){};

    float getPosition(Animation *pAnimation);

    void setPosition(float x);
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
    const map<MenuState, vector<EntryAnimation *>> *animations;
    const func_t function;

    Entry(bool enabled_on_pc, bool enabled_on_pi, const char *long_text,
          const char *short_text, char mnemonic, const char *action, const char *font,
          map<MenuState, vector<EntryAnimation *>> *animations,
          func_t function);
};

class MenuBuilder {
private:
    std::vector<Entry *> entries;
public:
    EntryBuilder &getEntryBuilder();

    MenuDefinition *build();

    friend void addEntry(MenuBuilder *mb, Entry *entry);
};


#endif //PIESCAPE2_MENUBUILDER_H
