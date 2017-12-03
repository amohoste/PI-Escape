#include "fake_led.h"

#include <windows.h>
// TODO #include <BiDiSpl.h> same as windows.h ?
#include <iostream>
#include <fstream>
using namespace std;

// Write bitmap to bmp file
void display_fake_ledgrid(const char* bits) {

}

// Create an empty square
void clear_fake_ledgrid() {

}

// Create one color square
void build_one_color_fake(SPGM_RGBTRIPLE colour) {
	// Bitmap file header
	BITMAPFILEHEADER file_header;
	file_header.bfOffBits = sizeof(BITMAPFILEHEADER); // size of the file header
	file_header.bfType = 0x4D42; // type of file = BM = 0x4D42
	file_header.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 32 * 32 * 3;	 // the size of the file in bytes

																							 // Bitmap info header
	BITMAPINFOHEADER info_header;
	info_header.biSize = sizeof(BITMAPINFOHEADER); // size of the info header
	info_header.biWidth = 32;
	info_header.biHeight = 32;
	info_header.biPlanes = 1;
	info_header.biBitCount = 24;
	info_header.biCompression = 0;
	info_header.biSizeImage = 0;
	info_header.biXPelsPerMeter = 0;
	info_header.biYPelsPerMeter = 0;
	info_header.biClrUsed = 0;
	info_header.biClrImportant = 0;

	char a[32 * 32 * 3];

	for (int i = 0; i < 32 * 32 * 3; i += 3) {
		a[i] = colour.rgbBlue;
		a[i + 1] = colour.rgbGreen;
		a[i + 2] = colour.rgbRed;
	}

	ofstream out;
	out.open("led.bmp", ios::binary);
	out.write((char*)&file_header, sizeof(BITMAPFILEHEADER));
	out.write((char*)&info_header, sizeof(BITMAPINFOHEADER));
	out.write((char*)&a, sizeof(a));
	out.close();
}

// Create rainbow square
void build_rainbow_fake() {

}

// Create square corresponding to the given colourmatrix
void build_array_fake(SPGM_RGBTRIPLE** square) {

}