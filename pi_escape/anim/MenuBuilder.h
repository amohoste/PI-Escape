#ifndef PIESCAPE2_MENUBUILDER_H
#define PIESCAPE2_MENUBUILDER_H

#include "Animation.h"
#include "Menu.h"

class Menu;

class EntryBuilder;

class MenuBuilder : public EntryBuilder{
public:
    EntryBuilder& addEntry();
    MenuDefinition* build();
};

#endif //PIESCAPE2_MENUBUILDER_H
