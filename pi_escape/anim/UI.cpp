#include "UI.h"

UIModel::UIModel() {

}

UIModel::~UIModel() {

}

UIView::UIView() {

}

UIView::~UIView() {

}

UIController::UIController() {

}

UIController::~UIController() {

}

void UIModel::setTime(uint64_t time) {
    this->time = time;
}

uint64_t UIModel::getTime() const {
    return time;
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
