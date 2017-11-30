#ifndef PIESCAPE2_MENU_H
#define PIESCAPE2_MENU_H

#include "UI.h"
#include "Animation.h"
#include "MenuBuilder.h"
#include "GameUICreator.h"

//TODO
class Entry;

class MenuDefinition {
public:
    const vector<Entry *> entries;

    MenuDefinition(vector<Entry *> entries);

    ~MenuDefinition();
};

class MenuModel : UIModel {
private:
    MenuDefinition *menuDefinition;
public:
    void setMenuDefinition(MenuDefinition *menuDefinition);
};

class MenuView : UIView {
    void draw() override;
};

class MenuController : UIController {

};

#endif //PIESCAPE2_MENU_H
