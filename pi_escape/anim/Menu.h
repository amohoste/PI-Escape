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
    int done;
public:
    MenuModel();

    void setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition);
    shared_ptr<MenuDefinition> getMenuDefinition();

    void setTime(uint64_t time) override;
    int isDone() const override;
    void setDone(int i);

    void addListener(MenuView *view);
    void fireInvalidationEvent();

};

class MenuView : UIView {
private:
    FontManager *fontManager;
    MenuModel *model;
    Graphics *graphics;
public:
    MenuView();
    void draw() override;
    vector<GlyphDrawCommand> drawEntry(Entry* entry, int x_offset, int y_offset);

    void setFontManager(FontManager *fm);
    void setGraphics(Graphics *graphics);
    void invalidated();
    void setModel(MenuModel *model);
};

class MenuController : UIController {
private:
    MenuModel *model;
public:
    ~MenuController() override ;
    void onKey(SDLKey key) override;
    void onExitKey() override;
    void setMenuModel(MenuModel *model);

};

#endif //PIESCAPE2_MENU_H
