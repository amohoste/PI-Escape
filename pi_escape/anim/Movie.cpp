#include "Movie.h"
#include "MovieBuilder.h"

#include <utility>

using namespace std;

MovieDefinition::MovieDefinition(deque<MovieAnimation *> movie_animations) : movie_animations(
        std::move(movie_animations)) {

}

void MovieModel::setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition) {
    time = 0;
    this->movieDefinition = std::move(movieDefinition);
    fireInvalidationEvent();
}

int MovieModel::isDone() const {
    //todo
    return 0;
}

shared_ptr<MovieDefinition> MovieModel::getMovieDefinition() {
    return movieDefinition;
}

MovieModel::MovieModel() {
    time = 0;
}

void MovieGLView::invalidated() {
//    Uint32 start = SDL_GetTicks();
    draw();
//    Uint32 end = SDL_GetTicks();
    model->setTime(model->getTime() + 1);
}

void MovieGLView::draw() {
    if (model->getMovieDefinition() != nullptr && !model->getMovieDefinition().get()->movie_animations.empty()) {
//        for (MovieAnimation *mv : model->getMovieDefinition().get()->movie_animations) {
//            if (model->getTime() > mv->getStart() && mv->getEnd() > model->getTime()) {
//                cout << mv->getText()  << " " << model->getTime() << endl;
//            }
//        }
    }
}

void MovieGLView::setMovieModel(MovieModel *movieModel) {
    this->model = movieModel;
}
