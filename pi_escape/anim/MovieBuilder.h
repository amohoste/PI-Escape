#ifndef PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
#define PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H

#include <bits/shared_ptr.h>
#include "Animation.h"
#include "Movie.h"

class EntryBuilder;

class MovieBuilder{
public:
    MovieBuilder& addText(const char* text);
    MovieBuilder& setFont(const char* text);
    MovieBuilder& setColor(t_vec4 color);
    MovieBuilder& setPos_percent(float x, float y);
    MovieBuilder& setStartTime(long l);
    MovieBuilder& setEndTime(long l);
    MovieBuilder& addAnimation(Animation* animation, long l, long p);
    MovieBuilder& endText();
    MovieBuilder& setDuration(long d);
    MovieDefinition* build();
};


#endif //PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
