#ifndef PIESCAPE2_MENU_H
#define PIESCAPE2_MENU_H


#include <deque>
#include <utility>
#include "UI.h"
#include "FontManager.h"
#include "MenuBuilder.h"
#include "Movie.h"

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
    t_vec3 *const color;

    MenuDefinition(vector<Entry *> entries, t_vec3 *color) : entries(std::move(entries)), color(color) {
    };

    ~MenuDefinition();
};

class MenuModel : public UIModel, public Subject {
private:
    vector<shared_ptr<MovieDefinition>> *movieDefinitions = new vector<shared_ptr<MovieDefinition>>;
    shared_ptr<MenuDefinition> menuDefinition;
    int selectedInt;

    vector<Level *> levels_to_play;

    bool activated_menu; //is er iets geactiveerd in het menu -> animatie spelen
public:

    MenuModel();

    ~MenuModel() override;

    vector<shared_ptr<MovieDefinition>> *getMovieDefinitions();

    void setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition);

    shared_ptr<MenuDefinition> getMenuDefinition();


    Entry *getSelectedEntry();

    vector<Level *> *getLevels();

    void setLevels(vector<Level *> levels);

    bool isActivated();

    void setActivated(bool i);

    void incrementSelectedInt(int i);

    void reset_start_times();

	int getSelectedInt();

    void selectFunction();
};

class LevelObserver;

/**
 * De menuview is ook een subject, namelijk welke input in het scherm komt
 */
class MenuView : public UIView, public Subject {
private:
    MoviePlayer *moviePlayer;
    MenuModel *menuModel;
    SDLKey key_press;

    vector<GlyphDrawCommand> drawEntry(Entry *entry, int x_offset, int y_offset);

    vector<GlyphDrawCommand> applyAnimations(vector<EntryAnimation *> animations, vector<GlyphDrawCommand> command);

    LevelObserver *levelObserver;

public:
    ~MenuView() override;

    void setFontManager(FontManager *fontManager) override;

    void draw() override;

    void invalidated() override;

    void setMenuModel(MenuModel *menuModel);

    SDLKey getKey_press();

    void setLevelObserver(LevelObserver *obs);

};


class MenuController : public UIController {
private:
    MenuModel *menuModel;
    MenuView *menuView;
public:
    void onKey(SDLKey key) override;

    void notified() override;

    void setMenuModel(MenuModel *menuModel);

    void setMenuView(MenuView *menuView);

    void up();

    void down();

    void select();

};

class LevelObserver : public Observer {
private:
    Graphics *graphics;
    MenuModel *menuModel;
public:
    LevelObserver(Graphics *graphics, MenuModel *menuModel) : graphics(graphics), menuModel(menuModel) {};

    void notified() override;

};

class MenuShower {
private:
    MenuView *mv;
    MenuModel *mm;
    MenuController *mc;
	//LedView *lv; ERROR!

    FontManager *fontManager;

    void clear();

public:
    explicit MenuShower(FontManager *fontManager) : fontManager(fontManager) {};

    ~MenuShower();

    void show(shared_ptr<MenuDefinition> menuDefinition);
};

#endif //PIESCAPE2_MENU_H
