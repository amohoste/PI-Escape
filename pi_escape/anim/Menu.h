#ifndef PIESCAPE2_MENU_H
#define PIESCAPE2_MENU_H


#include <deque>
#include "UI.h"
#include "FontManager.h"
#include "MenuBuilder.h"

extern "C" {
#include "../es/game.h"
};

class Entry;

class MenuView;

class MenuController;

class EntryAnimation;

float getPosition(uint64_t time, EntryAnimation *ea);

class MenuDefinition {
public:
    const deque<Entry *> entries;

    explicit MenuDefinition(deque<Entry *> entries);

    ~MenuDefinition();
};


class MenuModel : public UIModel, public Subject {
private:
    shared_ptr<MenuDefinition> menuDefinition;
    vector<MenuView *> listeners;
    int done;
    unsigned int selectedInt;
    Entry *selected;
    vector<Level *> *levels;

    map<Event, vector<Observer *>> observers;

    void updateSelected();

    bool visible;

    bool activated_menu;
public:

    void setVisible(bool v);

    bool isVisible();

    MenuModel();

    void setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition);

    shared_ptr<MenuDefinition> getMenuDefinition();

    void setTime(uint64_t time) override;

    int isDone() const override;

    void setDone(int i);

    void addListener(MenuView *view);

    void fireInvalidationEvent();

    void up();

    void down();

    void select();

    Entry *getSelectedEntry();

    vector<Level *> *getLevels();

    void setLevels(vector<Level *> *levels);

    void resetPositions();

    void playAnimations();

    bool isActivatedMenu();

    void setActivatedMenu(bool i);
};

class MenuView : UIView {
private:
    FontManager *fontManager;
    MenuModel *model;
    Graphics *graphics;
    MenuController *controller;
public:
    MenuView();

    void draw() override;

    vector<GlyphDrawCommand> drawEntry(Entry *entry, int x_offset, int y_offset, uint64_t time);

    void setFontManager(FontManager *fm);

    void setGraphics(Graphics *graphics);

    void invalidated();

    void setModel(MenuModel *model);

    void setController(MenuController *pController);

    void playActivationAnimations();
};

class MenuController : public UIController {
private:
    MenuModel *model;
public:
    ~MenuController() override;

    void onKey(SDLKey key) override;

    void onExitKey() override;

    void setMenuModel(MenuModel *model);

};

class LevelObserver : public Observer {
private:
    Graphics *graphics;
    Game *game;
    MenuModel *menuModel;
public:
    LevelObserver();

    ~LevelObserver();

    void notified() override;

    void setMenuModel(MenuModel *menuModel);
};

#endif //PIESCAPE2_MENU_H
