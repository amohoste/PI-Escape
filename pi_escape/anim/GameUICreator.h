#ifndef PIESCAPE2_GAMEUICREATOR_H
#define PIESCAPE2_GAMEUICREATOR_H

#include "Menu.h"
#include "Movie.h"

#include <string>
#include <utility>
#include <memory>

enum MenuState{ACTIVATE,OTHER_ACTIVATED,HOVER, DEFAULT};

class GameUICreator {
protected:
public:
    GameUICreator();

    virtual ~GameUICreator();

    std::shared_ptr<MenuDefinition> createGameMenu();

    std::shared_ptr<MovieDefinition> createIntro();

    std::shared_ptr<MovieDefinition> createCredits();

    std::shared_ptr<MovieDefinition> createOutro();
};

class EntryBuilder {
public:
    EntryBuilder &addAnimation(Animation* animation, MenuState activate, bool repeat, long duration);
    EntryBuilder& setEnabledOnPc(bool b);
    EntryBuilder& setEnabledOnPi(bool b);
    EntryBuilder& setLongText(const char* text);
    EntryBuilder& setShortText(const char* text);
    EntryBuilder& setFontName(const char* text);
    EntryBuilder& setMnemonic(char c);
    EntryBuilder& buildEntryWithAction(const char* action);
};

#endif //PIESCAPE2_GAMEUICREATOR_H
