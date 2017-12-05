#include "Movie.h"
#include "MovieBuilder.h"

#include <utility>

using namespace std;

MovieDefinition::MovieDefinition(deque<MovieAnimation *> movie_animations) : movie_animations(std::move(movie_animations)) {

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

void MovieGLView::invalidated() {
    cout << "invalidated" << endl;
    draw();
}

void MovieGLView::draw() {
    if(model->getMovieDefinition() != nullptr) {
        for (MovieAnimation *mv : model->getMovieDefinition().get()->movie_animations) {
            cout << mv->getText() << endl;
        }
    }
}

void MovieGLView::setMovieModel(MovieModel *movieModel) {
    this->model = movieModel;
    invalidated();
}
