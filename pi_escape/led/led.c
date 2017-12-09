#include "led.h"

void clear_ledgrid() {
#ifdef RPI
	clear_sense_ledgrid();
#endif // RPI
#ifndef RPI
	clear_fake_ledgrid();
#endif // !RPI
}

void build_one_color(SPGM_RGBTRIPLE colour) {
#ifdef RPI
	build_one_color_sense(colour);
#endif // RPI
#ifndef RPI
	build_one_color_fake(colour);
#endif // !RPI
}

void build_rainbow() {
#ifdef RPI
	build_rainbow_sense();
#endif // RPI
#ifndef RPI
	build_rainbow_fake();
#endif // !RPI
}

void build_array(SPGM_RGBTRIPLE** square) {
#ifdef RPI
	build_array_sense(square);
#endif // RPI
#ifndef RPI
	build_array_fake(square);
#endif // !RPI
}