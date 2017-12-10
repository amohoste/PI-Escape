#ifndef PIESCAPE2_GAMEUICREATOR_H
#define PIESCAPE2_GAMEUICREATOR_H

extern "C" {
#include "../level/levelloader.h"
};

#include "Menu.h"
#include "Movie.h"
#include "MenuBuilder.h"
#include "MovieBuilder.h"
#include "Animation.h"

#include <string>
#include <utility>
#include <memory>
#include <deque>


class MenuDefinition;

class GameUICreator {
protected:
public:
    GameUICreator();

    virtual ~GameUICreator();

    std::shared_ptr<MenuDefinition> createGameMenu();

    std::shared_ptr<MovieDefinition> createIntro();

    std::shared_ptr<MovieDefinition> createCredits();
	std::shared_ptr<MovieDefinition> createStarWarsCredits();

    std::shared_ptr<MovieDefinition> createOutro();
};


#endif //PIESCAPE2_GAMEUICREATOR_H
