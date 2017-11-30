#include "Movie.h"

using namespace std;
MovieDefinition::MovieDefinition(long duration, long start, long end, int x, int y, float *color, const char *font,
                                 const char *text) : duration(duration), start(start), end(end), x(x), y(y), color(color), font(font), text(text) {
}
