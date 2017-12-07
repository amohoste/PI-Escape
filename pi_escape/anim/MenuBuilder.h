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

/**
 * maakt een entry
 */
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

/**
 * Een animatie die over een entry moet lopen
 */
class EntryAnimation {
private:
    float position = 0;
    uint32_t start_time = 0;
public:
    const Animation *animation;
    const MenuState menuState;
    const long duration;
    const bool repeat;

    EntryAnimation(Animation *animation, MenuState menuState, bool repeat, long duration) : animation(animation),
                                                                                            menuState(menuState),
                                                                                            repeat(repeat),
                                                                                            duration(duration) {};

    float getPosition();

    void setPosition(float x);

    uint32_t getStartTime(){return start_time;}
    void setStartTime(uint32_t start_time){this->start_time = start_time;}
};

/**
 * Iets in het menu, start game enzo
 */
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
          func_t function) : enabled_on_pi(enabled_on_pi), enabled_on_pc(enabled_on_pc), long_text(long_text),
                             short_text(short_text), mnemonic(mnemonic), action(action), font(font),
                             animations(animations), function(function) {};
};

/**
 * Maakt het menu
 */
class MenuBuilder {
private:
    std::vector<Entry *> entries;
    t_vec3 color;
public:
    MenuBuilder();

    EntryBuilder &getEntryBuilder();

    MenuDefinition *build();

    friend void addEntry(MenuBuilder *mb, Entry *entry);

    void setBackGroundColor(t_vec4 color);
};


#endif //PIESCAPE2_MENUBUILDER_H
