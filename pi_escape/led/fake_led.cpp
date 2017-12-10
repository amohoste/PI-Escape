#ifndef RPI
#include "fake_led.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

// Timer
typedef std::chrono::milliseconds ms;
const ms write_every_ms = (ms) 1000;
chrono::system_clock::time_point last_write = chrono::system_clock::now();

// Constants
const int img_size = 256;	// width and heigth of the grid in pixels (should always be at least the amount of leds, 8)

const string bmp_file = "pi_escape/led/led.bmp";	// location of bmp file

// 8 by 8 resolution of rainbow pattern
const int rainbow[GRIDSIZE][GRIDSIZE][3] = {
	{ { 255,   0,   0 },{ 255, 128,   0 },{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 } },
	{ { 255, 128,   0 },{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 }},
	{ { 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 }},
	{ { 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 }},
	{ { 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 }},
	{ { 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 }},
	{ { 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },{ 255,   0,  64 }},
	{ { 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },{ 255,   0,  64 },{ 255,   0,   0 }}
};

// Create an empty square
void clear_fake_ledgrid() {
	chrono::system_clock::time_point now = chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last_write;
	ms d = std::chrono::duration_cast<ms>(elapsed_seconds);
	if (d < write_every_ms) {
		return;
	}

	// Construct black array
	SPGM_RGBTRIPLE** colours = new SPGM_RGBTRIPLE*[GRIDSIZE];
	SPGM_RGBTRIPLE colour;
	colour.rgbBlue = 0;
	colour.rgbGreen = 0;
	colour.rgbRed = 0;

	for (int i = 0; i < GRIDSIZE; i++) {
		colours[i] = new SPGM_RGBTRIPLE[GRIDSIZE];
		for (int j = 0; j < GRIDSIZE; j++) {
			colours[i][j] = colour;
		}
	}

	// Write array to file
	build_array_fake(colours);
	
	for (int i = 0; i < GRIDSIZE; i++)
		delete[] colours[i];
	delete[] colours;

	// Register write
	last_write = std::chrono::system_clock::now();
}

// Create one color square
void build_one_color_fake(SPGM_RGBTRIPLE colour) {
	chrono::system_clock::time_point now = chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last_write;
	ms d = std::chrono::duration_cast<ms>(elapsed_seconds);
	if (d < write_every_ms)
		return;

	// Construct monochroom array
	SPGM_RGBTRIPLE** colours = new SPGM_RGBTRIPLE*[GRIDSIZE];

	for (int i = 0; i < GRIDSIZE; i ++) {
		colours[i] = new SPGM_RGBTRIPLE[GRIDSIZE];
		for (int j = 0; j < GRIDSIZE; j ++) {
			colours[i][j] = colour;
		}
	}

	// write array to file
	build_array_fake(colours);

	// clean up
	for (int i = 0; i < GRIDSIZE; i++)
		delete[] colours[i];
	delete[] colours;

	// Register write
	last_write = std::chrono::system_clock::now();
}

// Create rainbow square
void build_rainbow_fake() {
	chrono::system_clock::time_point now = chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last_write;
	ms d = std::chrono::duration_cast<ms>(elapsed_seconds);
	if (d < write_every_ms) {
		return;
	}

	// Construct rainbow array
	SPGM_RGBTRIPLE** colours = new SPGM_RGBTRIPLE*[GRIDSIZE];
	for (int i = 0; i < GRIDSIZE; i++) {
		colours[i] = new SPGM_RGBTRIPLE[GRIDSIZE];
		for (int j = 0; j < GRIDSIZE; j++) {
			SPGM_RGBTRIPLE colour;
			colour.rgbRed = rainbow[i][j][0];
			colour.rgbGreen = rainbow[i][j][1];
			colour.rgbBlue = rainbow[i][j][2];

			colours[i][j] = colour;
		}
	}

	// write array to file
	build_array_fake(colours);

	// clean up
	for (int i = 0; i < GRIDSIZE; i++)
		delete[] colours[i];
	delete[] colours;

	// Register write
	last_write = std::chrono::system_clock::now();
}

// Create square corresponding to the given colourmatrix
void build_array_fake(SPGM_RGBTRIPLE** colours) {
	int Type = 0x4D42; // type of file = BM = 0x4D42
	int Size = 14 + sizeof(BITMAPINFOHEADER) + img_size * img_size * 3;	 // the size of the file in bytes
	int Reserved1 = 0;
	int Reserved2 = 0;


	char* bfType = new char[4];
	bfType[0] = (char)(Type >> 0);
	bfType[1] = (char)(Type >> 8);
	bfType[2] = (char)(Type >> 16);
	bfType[3] = (char)(Type >> 24);

	char* bfSize = new char[4];
	bfSize[0] = (char)(Size >> 0);
	bfSize[1] = (char)(Size >> 8);
	bfSize[2] = (char)(Size >> 16);
	bfSize[3] = (char)(Size >> 24);

	char* Reserves = new char[4];
	Reserves[0] = (char)(Reserved1 >> 0);
	Reserves[1] = (char)(Reserved1 >> 8);
	Reserves[2] = (char)(Reserved1 >> 16);
	Reserves[3] = (char)(Reserved1 >> 24);

	// Bitmap info header
	BITMAPINFOHEADER info_header;
	info_header.biSize = sizeof(BITMAPINFOHEADER); // size of the info header
	info_header.biWidth = img_size;
	info_header.biHeight = img_size;
	info_header.biPlanes = 1;
	info_header.biBitCount = 24;
	info_header.biCompression = 0;
	info_header.biSizeImage = 0;
	info_header.biXPelsPerMeter = 0;
	info_header.biYPelsPerMeter = 0;
	info_header.biClrUsed = 0;
	info_header.biClrImportant = 0;

	// Actual bits
	char bits[img_size * img_size * 3];
	int enlarge_factor = img_size / GRIDSIZE;
	int k = 0;
	for (int i = img_size - 1; i >= 0 ; i--) {
		for (int j = 0; j < img_size; j++) {
			SPGM_RGBTRIPLE colour = colours[i / enlarge_factor][j / enlarge_factor];
			bits[k] = colour.rgbBlue;
			bits[k + 1] = colour.rgbGreen;
			bits[k + 2] = colour.rgbRed;
			k += 3;
		}
	}

	// Write to bmp file
	ofstream out;
	out.open(bmp_file, ios::binary);

	out.write("BM", 2);
	out.write(bfSize, sizeof(bfSize));
	out.write(Reserves, sizeof(Reserves));
	out.write(Reserves, sizeof(Reserves));

	out.write((char*)&info_header, sizeof(BITMAPINFOHEADER));
	out.write((char*)&bits, sizeof(bits));
	out.close();

	delete[] bfType;
	delete[] bfSize;
	delete[] Reserves;
}
#endif // !RPI