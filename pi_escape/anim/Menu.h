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
class MenuView;

class MenuDefinition {
public:
    const vector<Entry *> entries;

    MenuDefinition(vector<Entry *> entries);

    ~MenuDefinition();
};

class MenuModel : UIModel {
private:
    shared_ptr<MenuDefinition> menuDefinition;
    vector<MenuView*> listeners;
public:
    MenuModel();

    void setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition);
    void setTime(uint64_t time) override;
    int isDone() const override;

    void addListener(MenuView *view);

    void fireInvalidationEvent();
};

class MenuView : UIView {
public:
    void draw() override;
    void invalidated();
};

class MenuController : UIController {

};

#endif //PIESCAPE2_MENU_H
