#include "Menu.h"

#include <utility>

using namespace std;

//TODO
MenuDefinition::MenuDefinition(vector<Entry *> entries) : entries(std::move(entries)) {

}

MenuDefinition::~MenuDefinition() {
    delete this->entries;
}

void MenuModel::setMenuDefinition(MenuDefinition *menuDefinition) {
    this->menuDefinition = menuDefinition;
}

void MenuView::draw() {

}
