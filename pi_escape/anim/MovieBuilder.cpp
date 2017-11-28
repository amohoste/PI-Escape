#include "MovieBuilder.h"

//TODO
MovieBuilder &MovieBuilder::addText(const char *text) {
    this->text = text;
    return *this;
}

MovieBuilder &MovieBuilder::setFont(const char *text) {
    //todo
    return *this;
}

MovieBuilder &MovieBuilder::setColor(float *color) {
    //todo
    return *this;
}

MovieBuilder &MovieBuilder::setPos_percent(float x, float y) {
    //todo
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
    //todo
    return *this;
}

MovieDefinition *MovieBuilder::build() {
    //todo
    return nullptr;
}
