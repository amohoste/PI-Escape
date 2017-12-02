#include "fake_led.h"

#include <BiDiSpl.h>
#include <iostream>
#include <fstream>
using namespace std;

void display_fake_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char*) {
	// Create bitmap

	// Write bitmap to bmp file
	//fstream bmp;
	//bmp.open("led.bmp", fstream::out);
	//&bmp.close;
	cout << "test\n";
}

void clear_fake_ledgrid() {

}

void build_one_color_fake(SPGM_RGBTRIPLE colour) {

}

void build_rainbow_fake() {

}