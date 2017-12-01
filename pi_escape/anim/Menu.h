#ifndef PIESCAPE2_MENU_H
#define PIESCAPE2_MENU_H

#include "UI.h"
#include "Animation.h"
#include "MenuBuilder.h"
#include "GameUICreator.h"
#include <memory>
#include <iostream>

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
    shared_ptr<MenuDefinition> menuDefinition;
public:
    void setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition);
    void setTime(uint64_t time) override;
    int isDone() const override;
};

class MenuView : UIView {
    void draw() override;
};

class MenuController : UIController {

};

#endif //PIESCAPE2_MENU_H
