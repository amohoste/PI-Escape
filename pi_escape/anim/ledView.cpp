#include "ledView.h"

/**
 * Constructor
 */
LedView::LedView() {

}

/**
 * Destructor
 */
LedView::~LedView() {

}

/**
 * React to change in selected menu item
 */
void LedView::notified() {
	printf("selction changed\n");
}

void LedView::setModel(MenuModel *model) {
	this->model = model;
	setSubject(model);
}