#include "Movie.h"
#include "MovieBuilder.h"

#include <utility>

using namespace std;

void MovieModel::setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition) {
    time = 0;
    this->movieDefinition = std::move(movieDefinition);
    setDone(false);
    fireInvalidationEvent();
}

shared_ptr<MovieDefinition> MovieModel::getMovieDefinition() {
    return movieDefinition;
}

MovieModel::~MovieModel() {
    //todo

}

/**
 *
 * @param ad  de animation
 * @param offset hoe lang is de movie al bezig voordat de animation komt?
 * @return de positie waarin de animatie zich bevind
 */
float MovieModel::getPosition(AnimationDuration *ad, int offset) {
    if(ad->start > time -offset){
        return 0;
    }
    float k = time - offset - ad->start;
    float d = k / ad->duration;
    return d > 1 ? 1 : d;
}

void MovieGLView::invalidated() {
    if (!model->isDone()) {
        Uint32 start = SDL_GetTicks();
        draw();
        Uint32 end = SDL_GetTicks();
        model->setTime(model->getTime() + end - start + 1);
    }
}

void MovieGLView::draw() {
    if (model->getMovieDefinition() != nullptr && !model->getMovieDefinition().get()->movie_animations.empty()) {
        vector<vector<GlyphDrawCommand>> commands; //alles dat getekend moet worden

        for (MovieAnimation *mv : model->getMovieDefinition().get()->movie_animations) {
            if (model->getTime() >= mv->start && mv->end > model->getTime()) {
                commands.push_back(glyphFromMovieAnimation(mv));
            }
        }

        //tekenen
        //todo fontmanager methode
        graphics_begin_draw(fontManager->graphics);
        for (vector<GlyphDrawCommand> vec : commands) {
            vector<GlyphDrawCommand>::iterator i = vec.begin();
            while (i != vec.end()) {
                this->fontManager->draw(*i);
                i++;
            }
        }
        graphics_end_draw(fontManager->graphics);

        //moet er nog verder getekend worden?
        model->setDone(model->getTime() >= model->getMovieDefinition().get()->duration);
    }
}

void MovieGLView::setMovieModel(MovieModel *movieModel) {
    this->model = movieModel;
}

vector<GlyphDrawCommand> MovieGLView::glyphFromMovieAnimation(MovieAnimation *mv) {
    FontManager *m = this->fontManager;

    // kleur, hpos en vpos opstellen voor volgende aanroep makeglyphdrawcommands
    m->setFont(mv->font);
    m->setHpos(TEXT_CENTER); // Default TEXT_LEFT
    m->setVpos(TEXT_MIDDLE); // DEFAULT TEXT_BOTTOM

    // Vector met glyphdrawcommands aanmaken
    vector<GlyphDrawCommand> command = m->makeGlyphDrawCommands(mv->text, (int) mv->x, (int) mv->y);

    for (AnimationDuration *a : mv->animations) {
        command = a->a->applyTransform(command, model->getPosition(a,(int) mv->start));
    }
    return command;
}


void MoviePlayer::play(shared_ptr<MovieDefinition> movieDefinition) {
    clear(); //oude componeten leegmaken
    mm = new MovieModel;
    mv = new MovieGLView;
//    mc = new MovieController;

    mm->addListener(mv);
    mv->setMovieModel(mm);
    mv->setFontManager(fontManager);

    mm->setMovieDefinition(std::move(movieDefinition));
}

void MoviePlayer::clear() {
        delete mm;
        delete mv;
        delete mc;
}

MoviePlayer::~MoviePlayer() {
    clear();
}


