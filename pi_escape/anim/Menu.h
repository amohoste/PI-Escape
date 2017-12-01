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

    explicit MenuDefinition(vector<Entry *> entries);

    ~MenuDefinition();
};

class MenuModel : UIModel {
private:
    shared_ptr<MenuDefinition> menuDefinition;
    vector<MenuView*> listeners;
public:
    MenuModel();

    void setMenuDefinition(const shared_ptr<MenuDefinition> &menuDefinition);
    void setTime(uint64_t time) override;
    int isDone() const override;

    void addListener(MenuView *view);

    void fireInvalidationEvent();

    shared_ptr<MenuDefinition> getMenuDefinition();
};

class MenuView : UIView {
private:
    MenuModel *model;
public:
    MenuView();
    void draw() override;
    void invalidated();
    void setModel(MenuModel *model);
};

class MenuController : UIController {

};

#endif //PIESCAPE2_MENU_H
