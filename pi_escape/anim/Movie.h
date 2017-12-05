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
    explicit MovieDefinition(deque<MovieAnimation *> movie_animations, long duration);

    const deque<MovieAnimation *> movie_animations;
    const long duration;
};


class MovieModel : public UIModel {
private:
    shared_ptr<MovieDefinition> movieDefinition;
    bool done;
public:
    MovieModel();
    int isDone() const override;
    void setDone(bool done);

public:
    void setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition);

    shared_ptr<MovieDefinition> getMovieDefinition();
};

class MovieGLView : public UIView {
private:
    MovieModel *model;
    vector<GlyphDrawCommand> getCommands(MovieAnimation *mv);
public:

    void setMovieModel(MovieModel *movieModel);

    void invalidated() override;

    void draw() override;

};

class MovieController : public UIController {
};

#endif //PIESCAPE2_ANIMATIONSEQUENCE_H
