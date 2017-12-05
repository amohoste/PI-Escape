#include "MovieBuilder.h"

MovieBuilder::MovieBuilder() : color(*new t_vec4[4]) {
}

MovieBuilder::~MovieBuilder() {
    delete[]&this->color;
}

MovieBuilder &MovieBuilder::addText(const char *text) {
    this->text = text;
    return *this;
}

MovieBuilder &MovieBuilder::setFont(const char *font) {
    this->font = font;
    return *this;
}

MovieBuilder &MovieBuilder::setColor(t_vec4 color) {
    glmc_assign_vec4(this->color, color);
    return *this;
}

MovieBuilder &MovieBuilder::setPos_percent(float x, float y) {
    this->x = 1920 * ((x - 50) / 100);
    this->y = 1080 * ((y - 50) / 100);
    return *this;
}

MovieBuilder &MovieBuilder::setStartTime(long l) {
    this->start = l;
    return *this;
}

MovieBuilder &MovieBuilder::setEndTime(long l) {
    this->end = l;
    return *this;
}

MovieBuilder &MovieBuilder::addAnimation(Animation *animation, long start, long duur) {
    this->animations.push_back(new AnimationDuration(start, duur, animation));
    return *this;
}

MovieBuilder &MovieBuilder::endText() {
    this->movie_animations.push_back(new MovieAnimation(text, start, end, font, color, x, y, end - start, animations));
    return *this;
}

MovieBuilder &MovieBuilder::setDuration(long d) {
    this->duration = d;
    return *this;
}

MovieDefinition *MovieBuilder::build() {
    return new MovieDefinition(movie_animations, duration);
}

MovieAnimation::MovieAnimation(const char *text, const long start, const long end, const char *font,
                               const t_vec4 &color, const float x,
                               const float y, const long duration, const vector<AnimationDuration *> animations) : text(text),
                                                                                                           start(start),
                                                                                                           end(end),
                                                                                                           font(font),
                                                                                                           color(color),
                                                                                                           x(x), y(y),
                                                                                                           duration(
                                                                                                                   duration),
                                                                                                           animations(
                                                                                                                   animations) {

}

AnimationDuration::AnimationDuration(long start, long duration, Animation *a) : start(start), duration(duration), a(a) {

}
