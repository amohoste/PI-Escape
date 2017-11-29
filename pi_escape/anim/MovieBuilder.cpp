#include "MovieBuilder.h"

//TODO
MovieBuilder &MovieBuilder::addText(const char *text) {
    this->text = text;
    return *this;
}

MovieBuilder &MovieBuilder::setFont(const char *font) {
    this->font = font;
    return *this;
}

MovieBuilder &MovieBuilder::setColor(t_vec4 color) {
    this->color = *color;
    return *this;
}

MovieBuilder &MovieBuilder::setPos_percent(float x, float y) {
    this->x =x;
    this->y =y;
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

MovieBuilder &MovieBuilder::addAnimation(Animation *animation, long l, long p) {
    //todo
    return *this;
}

MovieBuilder &MovieBuilder::endText() {
    //todo
    return *this;
}

MovieBuilder &MovieBuilder::setDuration(long d) {
    this->duration = d;
    return *this;
}

MovieDefinition *MovieBuilder::build() {
    //todo
    return nullptr;
}
