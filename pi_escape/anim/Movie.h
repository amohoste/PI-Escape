#ifndef PIESCAPE2_ANIMATIONSEQUENCE_H
#define PIESCAPE2_ANIMATIONSEQUENCE_H

#include "UI.h"
#include "Animation.h"

/**
 * A sequence of text animations, such as an intro, credits, ...
 */
class MovieDefinition {
public:
    MovieDefinition(long duration, long start, long end, float x, float y ,t_vec4& color, const char* font, const char* text);
    const long duration;
    const long start;
    const long end;
    const float x;
    const float y;
    const t_vec4& color;
    const char* font;
    const char* text;
};


class MovieModel : public UIModel {
    //TODO
};

class MovieGLView : public UIView {
    //TODO
};

class MovieController : public UIController {
    //TODO
    
};

#endif //PIESCAPE2_ANIMATIONSEQUENCE_H
