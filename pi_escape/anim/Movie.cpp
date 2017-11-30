#include "Movie.h"

using namespace std;
MovieDefinition::MovieDefinition(long duration, long start, long end, float x, float y, t_vec4& color, const char *font,
                                 const char *text, vector<Animation*> animations) : duration(duration), start(start), end(end), x(x), y(y), color(color), font(font), text(text), animations(animations) {
}
