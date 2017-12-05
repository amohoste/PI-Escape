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
	// Get text of selected item
	const char* str = this->model->getSelectedEntry()->long_text;

	// Convert to tinyFont
	// TODO
}

/**
 * Draw function of view
 */
void LedView::draw() {
	// Draw next frame of the tinyfont text
	// TODO
}

void LedView::setModel(MenuModel *model) {
	this->model = model;
}