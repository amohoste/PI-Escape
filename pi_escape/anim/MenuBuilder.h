#ifndef PIESCAPE2_MENUBUILDER_H
#define PIESCAPE2_MENUBUILDER_H

#include "Animation.h"
#include "Menu.h"

class Menu;

class EntryBuilder;

class MenuBuilder : public EntryBuilder{
public:
    MenuBuilder& addEntry();
    MenuBuilder& setEnabledOnPi(bool b);
    MenuBuilder& setEnabledOnPc(bool b);
    MenuBuilder& setLongText(const char* string);
    MenuBuilder& setShortText(const char* string);
    MenuBuilder& setFontName(const char* string);
    MenuBuilder& setMnemonic(char c);
    MenuBuilder& addAnimation(Animation animation);
    MenuBuilder& buildEntryWithAction(const char* string);

    MenuDefinition* build();
};

#endif //PIESCAPE2_MENUBUILDER_H
