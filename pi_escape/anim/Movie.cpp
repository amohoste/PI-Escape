#include "Movie.h"

#include <utility>

using namespace std;

MovieDefinition::MovieDefinition(deque<MovieAnimation *> movie_animations) : movie_animations(movie_animations) {

}

void MovieModel::setMovieDefinition(shared_ptr<MovieDefinition> movieDefinition) {
    time = 0;
    this->movieDefinition = std::move(movieDefinition);
}
