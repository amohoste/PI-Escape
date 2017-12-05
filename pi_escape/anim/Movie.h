#ifndef PIESCAPE2_ANIMATIONSEQUENCE_H
#define PIESCAPE2_ANIMATIONSEQUENCE_H

#include <deque>
#include "UI.h"
#include "Animation.h"

class MovieAnimation;

/**
 * A sequence of text animations, such as an intro, credits, ...
 */
class MovieDefinition {
public:
    explicit MovieDefinition(deque<MovieAnimation *> movie_animations);

    const deque<MovieAnimation *> movie_animations;
};


class MovieModel : public UIModel {
private:
    shared_ptr<MovieDefinition> movieDefinition;
public:
    int isDone() const override;

public:
    void setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition);

    shared_ptr<MovieDefinition> getMovieDefinition();
};

class MovieGLView : public UIView {
private:
    MovieModel *model;
public:

    void setMovieModel(MovieModel *movieModel);

    void invalidated() override;

    void draw() override;
};

class MovieController : public UIController {
};

#endif //PIESCAPE2_ANIMATIONSEQUENCE_H
