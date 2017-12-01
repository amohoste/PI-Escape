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

void MenuModel::setMenuDefinition(const shared_ptr<MenuDefinition> &menuDefinition) {
    this->menuDefinition = menuDefinition;
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

shared_ptr<MenuDefinition> MenuModel::getMenuDefinition() {
    return shared_ptr<MenuDefinition>();
}


void MenuView::draw() {
    const vector<Entry *> &entries = this->model->getMenuDefinition().get()->entries;
    if(!entries.empty()) {
        cout << "hallo" << endl;
        vector<Entry *>::const_iterator i = entries.begin();
        while (i != entries.end()) {
            cout << *i << endl;
            i++;
        }
    }
    cout << "gedaan" << endl;

}

void MenuView::invalidated() {
    cout << "I am invalidated" << endl;
    this->draw();
}

void MenuView::setModel(MenuModel *model) {
    this->model = model;

}

MenuView::MenuView() {

}

