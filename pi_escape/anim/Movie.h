#ifndef PIESCAPE2_ANIMATIONSEQUENCE_H
#define PIESCAPE2_ANIMATIONSEQUENCE_H

#include "UI.h"
#include "Animation.h"

/**
 * A sequence of text animations, such as an intro, credits, ...
 */
class MovieDefinition {
public:
    MovieDefinition(long duration);
    long duration;
//    const long start;
//    const long end;
//    const int x;
//    const int y;
//    const float color;
//    const char* font;
//    const char* text;
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
