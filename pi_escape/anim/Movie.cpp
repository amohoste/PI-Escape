#include "Movie.h"
#include "MovieBuilder.h"

#include <utility>

float getPosition(MovieAnimation *pAnimation, uint64_t time);

using namespace std;

MovieDefinition::MovieDefinition(deque<MovieAnimation *> movie_animations, long duration) : movie_animations(
        std::move(movie_animations)), duration(duration) {

}

void MovieModel::setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition) {
    time = 0;
    this->movieDefinition = std::move(movieDefinition);
    done = false;
    fireInvalidationEvent();
}

int MovieModel::isDone() const {
    return done;
}

shared_ptr<MovieDefinition> MovieModel::getMovieDefinition() {
    return movieDefinition;
}

MovieModel::MovieModel() {
    time = 0;
}

void MovieModel::setDone(bool done) {
    this->done = done;
}

void MovieGLView::invalidated() {
    if (!model->isDone()) {
        Uint32 start = SDL_GetTicks();
        draw();
        Uint32 end = SDL_GetTicks();
        model->setTime(model->getTime() + end - start);
    }
}

void MovieGLView::draw() {
    if (model->getMovieDefinition() != nullptr && !model->getMovieDefinition().get()->movie_animations.empty()) {
        vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden

        for (MovieAnimation *mv : model->getMovieDefinition().get()->movie_animations) {
            if (model->getTime() >= mv->start && mv->end > model->getTime()) {
                commands.push_back(getCommands(mv));
            }
        }

        //tekenen
        graphics_begin_draw(fontManager->graphics);
        for (vector<GlyphDrawCommand> vec : commands) {
            vector<GlyphDrawCommand>::iterator i = vec.begin();
            while (i != vec.end()) {
                this->fontManager->draw(*i);
                i++;
            }
        }
        graphics_end_draw(fontManager->graphics);
        model->setDone(model->getTime() >= model->getMovieDefinition().get()->duration);
    }
}

void MovieGLView::setMovieModel(MovieModel *movieModel) {
    this->model = movieModel;
}

vector<GlyphDrawCommand> MovieGLView::getCommands(MovieAnimation *mv) {
    FontManager *m = this->fontManager;

    // Font, kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
    m->setColor(0.4f, 0.4f, 0.4f, 1.0f); // Default { 1.0f, 0.0f, 0.0f, 1.0f }
    m->setFont(mv->font);
    m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
    m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

    // Vector met glyphdrawcommands aanmaken
    vector<GlyphDrawCommand> command = m->makeGlyphDrawCommands(mv->text, (int) mv->x, (int) mv->y);

    for (Animation *a : mv->animations) {
        command = a->applyTransform(command, getPosition(mv, model->getTime()));
    }
    return command;
}

float getPosition(MovieAnimation *mv, uint64_t time) {
    float a = time - mv->start;
    return a/mv->duration;
}

