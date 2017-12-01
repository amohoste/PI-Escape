#include "Menu.h"

#include <utility>

using namespace std;

//TODO
MenuDefinition::MenuDefinition(vector<Entry *> entries) : entries(std::move(entries)) {

}

MenuDefinition::~MenuDefinition() {
    //entries
    //listeners
}

void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition = std::move(menuDefinition);
    this->fireInvalidationEvent();
}

void MenuModel::setTime(uint64_t) {
    //todo
}

int MenuModel::isDone() const {
    //todo
    return 0;
}

MenuModel::MenuModel() {

}

void MenuModel::addListener(MenuView *view) {
    this->listeners.push_back(view);
}

void MenuModel::fireInvalidationEvent() {
    for(int i =0; i <this->listeners.size(); i++){
        this->listeners[i]->invalidated();
    }
}


void MenuView::draw() {
    cout << "functie draw opgeroepen" << endl;

}

void MenuView::invalidated() {
    cout << "I am invalidated" << endl;
    this->draw();
}
