#include "fake_led.h"

#include <BiDiSpl.h>
#include <iostream>
#include <fstream>
using namespace std;

// Write bitmap to bmp file
void display_fake_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char*) {
	//fstream bmp;
	//bmp.open("led.bmp", fstream::out);
	//&bmp.close;
}

// Create an empty square
void clear_fake_ledgrid() {

}

// Create one color square
void build_one_color_fake(SPGM_RGBTRIPLE colour) {

}

// Create rainbow square
void build_rainbow_fake() {

}

// Create square corresponding to the given colourmatrix
void build_array_fake(SPGM_RGBTRIPLE** square) {

}