#include "MovieBuilder.h"

MovieBuilder::MovieBuilder(): color(*new t_vec4[4]){
}

MovieBuilder::~MovieBuilder(){
    delete []& this->color;
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
    return new MovieDefinition(this->duration, this->start, this->end,this->x, this->y, this->color, this->font, this->text);
}
