#ifndef PIESCAPE2_ANIMATIONSEQUENCE_H
#define PIESCAPE2_ANIMATIONSEQUENCE_H

#include <deque>
#include <utility>
#include "UI.h"
#include "Animation.h"
#include "MovieBuilder.h"

class MovieAnimation;
class AnimationDuration;

/**
 * A sequence of text animations, such as an intro, credits, ...
 */
class MovieDefinition {
public:
    explicit MovieDefinition(vector<MovieAnimation *> movie_animations, long duration) : movie_animations(
            std::move(movie_animations)), duration(duration) {};

    const vector<MovieAnimation *> movie_animations;
    const long duration; //hoelang duurt de movie
};


class MovieModel : public UIModel {
private:
    shared_ptr<MovieDefinition> movieDefinition{};


public:
    ~MovieModel() override;

    void setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition);

    shared_ptr<MovieDefinition> getMovieDefinition();

    float getPosition(AnimationDuration *ad);

};

class MovieGLView : public UIView {
private:
    MovieModel *model;

    vector<GlyphDrawCommand> glyphFromMovieAnimation(MovieAnimation *mv);

public:
    void setMovieModel(MovieModel *movieModel);

    void invalidated() override;

    void draw() override;
};

class MovieController : public UIController {
};


class MoviePlayer {
private:
    MovieGLView *mv{};
    MovieModel *mm{};
    MovieController *mc{};

    FontManager *fontManager;

    void clear();

public:
    explicit MoviePlayer(FontManager *fontManager) : fontManager(fontManager) {};

    ~MoviePlayer();

    void play(shared_ptr<MovieDefinition> movieDefinition);
};

#endif //PIESCAPE2_ANIMATIONSEQUENCE_H
