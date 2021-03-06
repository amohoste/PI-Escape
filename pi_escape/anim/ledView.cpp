#include "ledView.h"

#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;

// constants
const int PADDING = GRIDSIZE;
const int HEIGHT_PATTERN = 6;
const string TINYFONT = "pi_escape/led/TinyFont";

typedef std::chrono::milliseconds ms;
const ms draw_every_ms = (ms)100;
chrono::system_clock::time_point last_draw = chrono::system_clock::now();

/**
* Constructor
*/
LedView::LedView() {
	// init fields
	this->length_pattern = 0;
	this->frame = 0;
	this->pattern = new int*[HEIGHT_PATTERN];
	for (int i = 0; i < HEIGHT_PATTERN; i++) {
		this->pattern[i] = new int[length_pattern];
	}

	// read Tiny Font file
	int length = 3;
	char* buffer = new char[length];

	ifstream file;
	file.open(TINYFONT, ios::in);

	int k = 0;
	this->tiny_font = new char*[79];
	while (file.read(buffer, length)) {
		this->tiny_font[k] = new char[79];
		this->tiny_font[k][0] = buffer[1];
		this->tiny_font[k][1] = buffer[2];
		k++;
	}

	file.close();

	delete[] buffer;
}

/**
* Destructor
*/
LedView::~LedView() {
	delete[] this->tiny_font;

	for (int i = 0; i < HEIGHT_PATTERN; i++) {
		delete[] this->pattern[i];
	}
	delete[] this->pattern;
}

/**
* React to change in selected menu item
*/
void LedView::notified() {
	// Get text of selected item
	const string str = this->model->getSelectedEntry()->long_text;

	// Reallocate pattern
	for (int i = 0; i < HEIGHT_PATTERN; i++) {
		delete[] this->pattern[i];
	}
	delete[] this->pattern;

	this->length_pattern = str.length() * 4 + PADDING;
	this->pattern = new int*[HEIGHT_PATTERN];
	for (int i = 0; i < HEIGHT_PATTERN; i++) {
		this->pattern[i] = new int[length_pattern];
	}

	for (int i = 0; i < HEIGHT_PATTERN; i++) {
		for (int j = 0; j < length_pattern; j++) {
			this->pattern[i][j] = 0;
		}
	}

	// Convert to TinyFont
	for (int j = 0; j < str.length(); j++) {	// go over each character
		int ascii = str[j];
		// Get bytes
		unsigned char byte1;
		unsigned char byte2;
		if (47 < ascii && ascii < 127) {	// ascii value must be in range of TinyFont [48, 126]
			byte1 = this->tiny_font[ascii - 48][1];
			byte2 = this->tiny_font[ascii - 48][0];
		}
		else {	// else make an empty screen
			byte1 = 0x00;
			byte2 = 0x00;
		}

		// start location for byte1
		int ra = 0;
		int ka = 0;

		// start location for byte2
		int rb = 2;
		int kb = 1;

		int empty_line;	// location of empty line
						// if bit 16 is 1 fill first lines with zeros
		if (!!(byte1 & 0x80)) {
			empty_line = 1;
		}
		else { // else fill the last lines with zeros
			empty_line = 0;
		}

		int a = !!(byte1 & 0x80);
		int b = !!(byte2 & 0x80);
		this->pattern[rb + empty_line][kb + (j * 4) + PADDING] = b;
		kb++;
		for (int i = 1; i < GRIDSIZE; i++) {
			a = !!((byte1 << i) & 0x80);
			b = !!((byte2 << i) & 0x80);
			this->pattern[ra + empty_line][ka + (3 * j) + j + PADDING] = a;
			this->pattern[rb + empty_line][kb + (3 * j) + j + PADDING] = b;
			ka = (ka + 1) % 3;
			kb = (kb + 1) % 3;
			if (ka == 0) ra++;
			if (kb == 0) rb++;
		}
	}
	
	this->frame = 0;
}

/**
* Draw function of view
*/
void LedView::draw() {
	// construct frame
	SPGM_RGBTRIPLE** frame;
	frame = new SPGM_RGBTRIPLE*[GRIDSIZE];
	for (int i = 0; i < GRIDSIZE; i++) {
		frame[i] = new SPGM_RGBTRIPLE[GRIDSIZE];
	}

	// add text
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE; j++) {
			SPGM_RGBTRIPLE colour;
			int row = i - 1;
			int column = (this->frame + j < this->length_pattern) ? this->frame + j : j;
			if (0 < i && i <= HEIGHT_PATTERN && this->pattern[row][column]) {
				colour.rgbBlue = 0;
				colour.rgbGreen = 0;
				colour.rgbRed = 255;
			} else {
				colour.rgbBlue = 0;
				colour.rgbGreen = 0;
				colour.rgbRed = 0;
			}

			frame[i][j] = colour;
		}
	}

	// add indicators
	SPGM_RGBTRIPLE inside;
	inside.rgbBlue = 0;
	inside.rgbGreen = 255;
	inside.rgbRed = 50;

	SPGM_RGBTRIPLE outside;
	outside.rgbBlue = 0;
	outside.rgbGreen = 225;
	outside.rgbRed = 150;

	if (model->getSelectedInt() > 0) {
		frame[0][3] = inside;
		frame[0][4] = inside;
	}
	
	if (model->getSelectedInt() > 1) {
		frame[0][2] = outside;
		frame[0][5] = outside;
	}

	if (model->getSelectedInt() < model->getMenuDefinition().get()->entries.size() - 1) {
		frame[GRIDSIZE - 1][3] = inside;
		frame[GRIDSIZE - 1][4] = inside;
	}

	if (model->getSelectedInt() < model->getMenuDefinition().get()->entries.size() - 2) {
		frame[GRIDSIZE - 1][2] = outside;
		frame[GRIDSIZE - 1][5] = outside;
	}

	// draw
	build_array(frame);

	// Register draw
	last_draw = std::chrono::system_clock::now();
	this->frame = (this->frame + 1) % this->length_pattern;

	for (int i = 0; i < GRIDSIZE; i++) {
		delete[] frame[i];
	}
	delete[] frame;
}

/**
* invalidated
*/
void LedView::invalidated() {
	// draw next frame of the tinyfont text
	// granted enough time as passed
	chrono::system_clock::time_point now = chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last_draw;
	ms d = std::chrono::duration_cast<ms>(elapsed_seconds);
	if (!model->isDone() && this->length_pattern > 0 && d > draw_every_ms) {
		draw();
	} else if (model->isDone() && !model->isActivated()) {
		clear_ledgrid();
	}
}

void LedView::setModel(MenuModel *model) {
	this->model = model;
}