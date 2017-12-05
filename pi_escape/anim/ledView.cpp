#include "ledView.h"

#include <iostream>
#include <fstream>
using namespace std;

/**
 * Constructor
 */
LedView::LedView() {
	// Read Tiny Font file
	int length = 3;
	char* buffer = new char[length];

	ifstream file;
	file.open("pi_escape/led/TinyFont", ios::in);

	int k = 0;
	this->tiny_font = new char[79 * 2];
	while (file.read(buffer, length)) {
		this->tiny_font[k] = buffer[1];
		this->tiny_font[k + 1] = buffer[2];
		k += 2;
	}

	file.close();

	delete[] buffer;
}

/**
 * Destructor
 */
LedView::~LedView() {
	delete[] this->tiny_font;
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