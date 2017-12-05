#include "UI.h"

UIModel::UIModel() {

}

UIModel::~UIModel() {

}

UIView::UIView() {

}

UIView::~UIView() {

}

void UIView::setFontManager(FontManager *fm) {
    this->fontManager = fm;
}

void Observable::addListener(Listener *listener) {
    this->listeners.push_back(listener);
}
void Observable::fireInvalidationEvent() {
    for (auto &listener : this->listeners) {
        listener->invalidated();
    }
}

UIController::UIController() {

}

UIController::~UIController() {

}

void UIModel::setTime(uint64_t time) {
    this->time = time;
    fireInvalidationEvent();
}

uint64_t UIModel::getTime() const {
    return time;
}

int UIModel::isDone() const {
    return done;
}

int UIModel::setDone(bool done) {
    this->done = done;
}

void Observer::setSubject(Subject *subject) {
    this->subject = subject;
}

void Observer::notified() {

}


void Subject::registerObserver(Event e,Observer *o) {
    observers[e].push_back(o);
}

void Subject::notify(Event e) {
    for(Observer* o : observers[e]){
        o->notified();
    }
}
