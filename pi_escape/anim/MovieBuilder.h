#ifndef PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
#define PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H

#include "Animation.h"
#include "Movie.h"
#include "glmc.h"

class EntryBuilder;
class AnimationDuration;

class MovieBuilder {
private:
    const char *text;
    long start;
    long end;
    const char *font;
    t_vec4 &color;
    float x;
    float y;
    long duration;
    std::vector<AnimationDuration *> animations;
    std::deque<MovieAnimation *> movie_animations;
public:
    MovieBuilder();

    ~MovieBuilder();

    MovieBuilder &addText(const char *text);

    MovieBuilder &setFont(const char *font);

    MovieBuilder &setColor(t_vec4 color);

    MovieBuilder &setPos_percent(float x, float y);

    MovieBuilder &setStartTime(long l);

    MovieBuilder &setEndTime(long l);

    MovieBuilder &addAnimation(Animation *animation, long l, long p);

    MovieBuilder &endText();

    MovieBuilder &setDuration(long d);

    MovieDefinition *build();
};

class AnimationDuration{
public:
    const long start;
    const long duration;
    const Animation *a;

    AnimationDuration(long start, long duration, Animation *a);
};

class MovieAnimation {
public:
    const char *text;
    const long start;
    const long end;
    const char *font;
    const t_vec4 &color;
    const float x;
    const float y;
    const long duration;
    const std::vector<AnimationDuration *> animations;
    MovieAnimation(const char *text, const long start, const long end, const char *font, const t_vec4 &color,
                   const float x, const float y, const long duration, const std::vector<AnimationDuration *> animations);

};


#endif //PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
