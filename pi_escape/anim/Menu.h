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

class MenuDefinition {
public:
    const vector<Entry *> entries;

    explicit MenuDefinition(vector<Entry *> entries) : entries(entries) {};

    ~MenuDefinition() {

    }
};


class MenuModel : public UIModel, public Subject {
private:
    shared_ptr<MenuDefinition> menuDefinition;
    unsigned int selectedInt;

//    Entry *selected;

    vector<Level *> *levels_to_play;

//    bool activated_menu;
public:
    MenuModel() {

    }

    void setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition);

    shared_ptr<MenuDefinition> getMenuDefinition();

    void up();

    void down();

    void select();

    Entry *getSelectedEntry();

    vector<Level *> *getLevels();

    void setLevels(vector<Level *> *levels);

//    void resetPositions();
//
//    void playAnimations();
//
//    bool isActivatedMenu();
//
//    void setActivatedMenu(bool i);
};

/**
 * De menuview is ook een subject, namelijk welke input in het scherm komt
 */
class MenuView : public UIView, public Subject {
private:
    MenuModel *menuModel;
//    bool animationsFinished;
//    Uint32 last_update = SDL_GetTicks();
public:
//    MenuView();
    ~MenuView() override {

    }

    void draw() override;

//
    vector<GlyphDrawCommand> drawEntry(Entry *entry, int x_offset, int y_offset);

//
    void invalidated() override;

//
    void setMenuModel(MenuModel *menuModel);
//
//    void setController(MenuController *pController);


    vector<GlyphDrawCommand> applyAnimations(vector<EntryAnimation*> animations, vector<GlyphDrawCommand> command);
};


class MenuController : public UIController {
private:
    MenuModel *menuModel;
    MenuView *menuView;
public:
    ~MenuController() override {

    }

    void onKey(SDLKey key) override;

    void onExitKey() override {

    }

//
    void setMenuModel(MenuModel *menuModel);

    void setMenuView(MenuView *menuView);

};

class LevelObserver : public Observer {
private:
//    Graphics *graphics;
//    Game *game;
    MenuModel *menuModel;
public:
//    LevelObserver();
//
//    ~LevelObserver();
//
//    void notified() override;
//
    void setMenuModel(MenuModel *menuModel);
};

class MenuShower {
private:
    MenuView *mv{};
    MenuModel *mm{};
    MenuController *mc{};

    FontManager *fontManager;

    void clear();

public:
    explicit MenuShower(FontManager *fontManager) : fontManager(fontManager) {};

    ~MenuShower();

    void show(shared_ptr<MenuDefinition> menuDefinition);
};

#endif //PIESCAPE2_MENU_H
