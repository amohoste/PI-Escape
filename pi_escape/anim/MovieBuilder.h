#ifndef PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
#define PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H

#include <bits/shared_ptr.h>
#include "Animation.h"
#include "Movie.h"

class EntryBuilder;

class MovieBuilder : public EntryBuilder{
public:
    MovieBuilder& setDuration(long l);
    MovieBuilder& addText(const char* string);
    MovieBuilder& setFont(const char* string);
    MovieBuilder& setColor(t_vec4 color);
    MovieBuilder& setPos_percent(float x, float y);
    MovieBuilder& setStartTime(long start);
    MovieBuilder& setEndTime(long end);

    std::shared_ptr<MovieDefinition> build();


};

#endif //PIESCAPE2_ANIMATIONSEQUENCEBUILDER_H
