#ifndef PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
#define PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H

#include "Animation.h"
#include "Movie.h"
#include "glmc.h"

class EntryBuilder;

class MovieBuilder {
private:
    const char *text;
    long start;
    long end;
    const char *font;
    t_vec4& color;
    float x;
    float y;
    long duration;
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


#endif //PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
