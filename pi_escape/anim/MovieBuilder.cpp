#include "MovieBuilder.h"

MovieBuilder::MovieBuilder() {
    t_vec4 col2 = {1.0f, 0.0f, 0.0f, 1.0f};
    glmc_assign_vec4(this->color, col2);
}

MovieBuilder::~MovieBuilder() {
	vector<AnimationDuration *>::iterator it = animations.begin();

	while (it != animations.end()) {
		delete(*it);
		it++;
	}
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
    this->x_perc = x;
    this->y_perc = y;
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
    t_vec4 *color = new t_vec4[4];
    memcpy(color, this->color, sizeof(t_vec4));
    this->movie_animations.push_back(
            new MovieAnimation(text, start, end, font, color, x_perc, y_perc, end - start, animations));
    animations.clear();
    return *this;
}

MovieBuilder &MovieBuilder::setDuration(long d) {
    this->duration = d;
    return *this;
}

MovieDefinition *MovieBuilder::build() {
    t_vec3 *background = new t_vec3[3];
    memcpy(background, this->background_color, sizeof(t_vec3));
    return new MovieDefinition(movie_animations, duration, background);
}

MovieBuilder &MovieBuilder::setBackgroundColor(t_vec3 color) {
    glmc_assign_vec3(this->background_color, color);
    return *this;
}

MovieAnimation::MovieAnimation(const char *text, const long start, const long end, const char *font,
                               t_vec4 *color, const float x,
                               const float y, const long duration, const vector<AnimationDuration *> animations) : text(
        text),
                                                                                                                   start(start),
                                                                                                                   end(end),
                                                                                                                   font(font),
                                                                                                                   color(color),
                                                                                                                   x(x),
                                                                                                                   y(y),
                                                                                                                   duration(
                                                                                                                           duration),
                                                                                                                   animations(
                                                                                                                           animations) {

}

MovieAnimation::~MovieAnimation() {
    delete[] color;
    for(AnimationDuration* a : animations){
        delete(a);
    }
}

AnimationDuration::AnimationDuration(long start, long duration, Animation *a) : start(start), duration(duration), a(a) {

}

AnimationDuration::~AnimationDuration() {
    delete a;
}
