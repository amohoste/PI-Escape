#include "fake_led.h"

#include <windows.h>
// TODO #include <BiDiSpl.h> same as windows.h ?
#include <iostream>
#include <fstream>
using namespace std;

const int grid_size = 256;

int rainbow[8][8][3] = {
	{ { 255,   0,   0 },{ 255, 128,   0 },{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 } },
	{ { 255, 128,   0 },{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 }},
	{ { 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 }},
	{ { 255, 191,   0 },{ 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 }},
	{ { 255, 255,   0 },{ 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 }},
	{ { 0, 255,   0 },{ 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 }},
	{ { 0, 255, 128 },{ 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },{ 255,   0,  64 }},
	{ { 0, 255, 255 },{ 0, 191, 255 },{ 0, 104, 255 },{ 64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },{ 255,   0,  64 },{ 255,   0,   0 }}
};

// Write bitmap to bmp file
void display_fake_ledgrid(char bits[]) {
	
}

// Create an empty square
void clear_fake_ledgrid() {
	SPGM_RGBTRIPLE** colours = new SPGM_RGBTRIPLE*[grid_size];
	SPGM_RGBTRIPLE colour;
	colour.rgbBlue = 0;
	colour.rgbGreen = 0;
	colour.rgbRed = 0;

	for (int i = 0; i < grid_size; i++) {
		colours[i] = new SPGM_RGBTRIPLE[grid_size];
		for (int j = 0; j < grid_size; j++) {
			colours[i][j] = colour;
		}
	}

	build_array_fake(colours);
	
	for (int i = 0; i < grid_size; i++)
		delete[] colours[i];
	delete[] colours;
}

// Create one color square
void build_one_color_fake(SPGM_RGBTRIPLE colour) {
	SPGM_RGBTRIPLE** colours = new SPGM_RGBTRIPLE*[grid_size];

	for (int i = 0; i < grid_size; i ++) {
		colours[i] = new SPGM_RGBTRIPLE[grid_size];
		for (int j = 0; j < grid_size; j ++) {
			colours[i][j] = colour;
		}
	}

	build_array_fake(colours);

	for (int i = 0; i < grid_size; i++)
		delete[] colours[i];
	delete[] colours;
}

// Create rainbow square
void build_rainbow_fake() {
	SPGM_RGBTRIPLE** colours = new SPGM_RGBTRIPLE*[grid_size];

	int enlarge_factor = grid_size/8;

	for (int i = 0; i < grid_size; i++) {
		colours[i] = new SPGM_RGBTRIPLE[grid_size];
		for (int j = 0; j < grid_size; j++) {
			SPGM_RGBTRIPLE colour;
			colour.rgbRed = rainbow[i / enlarge_factor][j / enlarge_factor][0];
			colour.rgbGreen = rainbow[i / enlarge_factor][j / enlarge_factor][1];
			colour.rgbBlue = rainbow[i / enlarge_factor][j / enlarge_factor][2];

			colours[i][j] = colour;
		}
	}

	build_array_fake(colours);

	for (int i = 0; i < grid_size; i++)
		delete[] colours[i];
	delete[] colours;
}

// Create square corresponding to the given colourmatrix
void build_array_fake(SPGM_RGBTRIPLE** colours) {
	// Bitmap file header
	BITMAPFILEHEADER file_header;
	file_header.bfOffBits = sizeof(BITMAPFILEHEADER); // size of the file header
	file_header.bfType = 0x4D42; // type of file = BM = 0x4D42
	file_header.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + grid_size * grid_size * 3;	 // the size of the file in bytes

	// Bitmap info header
	BITMAPINFOHEADER info_header;
	info_header.biSize = sizeof(BITMAPINFOHEADER); // size of the info header
	info_header.biWidth = grid_size;
	info_header.biHeight = grid_size;
	info_header.biPlanes = 1;
	info_header.biBitCount = 24;
	info_header.biCompression = 0;
	info_header.biSizeImage = 0;
	info_header.biXPelsPerMeter = 0;
	info_header.biYPelsPerMeter = 0;
	info_header.biClrUsed = 0;
	info_header.biClrImportant = 0;

	// Actual bits
	char a[grid_size * grid_size * 3];
	int k = 0;
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			SPGM_RGBTRIPLE colour = colours[i][j];
			a[k] = colour.rgbBlue;
			a[k + 1] = colour.rgbGreen;
			a[k + 2] = colour.rgbRed;
			k += 3;
		}
	}

	// Write to bmp file
	ofstream out;
	out.open("led.bmp", ios::binary);
	out.write((char*)&file_header, sizeof(BITMAPFILEHEADER));
	out.write((char*)&info_header, sizeof(BITMAPINFOHEADER));
	out.write((char*)&a, sizeof(a));
	out.close();
}