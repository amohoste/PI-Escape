#include "Menu.h"

#include <utility>

using namespace std;

//TODO
MenuDefinition::MenuDefinition(vector<Entry *> entries) : entries(std::move(entries)) {

}

MenuDefinition::~MenuDefinition() {
    //entries
}

void MenuModel::setMenuDefinition(shared_ptr<MenuDefinition> menuDefinition) {
    this->menuDefinition = menuDefinition;
}

void MenuModel::setTime(uint64_t) {
    //todo
}

int MenuModel::isDone() const {
    //todo
    return 0;
}



void MenuView::draw() {
    cout << "functie draw opgeroepen" << endl;

}
