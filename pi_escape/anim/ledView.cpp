#include "ledView.h"

#include <iostream>
#include <fstream>
using namespace std;

// constants
const int HEIGHT_PATTERN = 6;
const string TINYFONT = "pi_escape/led/TinyFont";

/**
 * Constructor
 */
LedView::LedView() {
	// init fields
	this->length_pattern = 1;
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
}

/**
 * React to change in selected menu item
 */
void LedView::notified() {
	// TODO fix i and if i or " " remove whitespace(optional)
	// Get text of selected item
	const string str = this->model->getSelectedEntry()->long_text;

	// Reallocate pattern
	for (int i = 0; i < HEIGHT_PATTERN; i++) {
		delete[] this->pattern[i];
	}
	delete[] this->pattern;

	this->length_pattern = str.length() * 3 + (str.length() - 1);
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

	//for (int i = 0; i < HEIGHT_PATTERN; i++) {
	//	for (int j = 0; j < this->length_pattern; j++) {

	//	}
	//}

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
		} else { // else fill the last lines with zeros
			empty_line = 0;
		}
		
		int a = !!(byte1 & 0x80);
		int b = !!(byte2 & 0x80);
		this->pattern[rb + empty_line][kb + (j * 4)] = b;
		kb++;
		for (int i = 1; i < 8; i++) {
			a = !!((byte1 << i) & 0x80);
			b = !!((byte2 << i) & 0x80);
			this->pattern[ra + empty_line][ka + (3 * j) + j] = a;
			this->pattern[rb + empty_line][kb + (3 * j) + j] = b;
			ka = (ka + 1) % 3;
			kb = (kb + 1) % 3;
			if (ka == 0) ra++;
			if (kb == 0) rb++;
		}
	}

	for (int i = 0; i < HEIGHT_PATTERN; ++i)
	{
		for (int j = 0; j < this->length_pattern; ++j)
		{
			std::cout << this->pattern[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	printf("\n");
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