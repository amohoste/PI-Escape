#include "led.h"

void display_ledgrid(SPGM_RGBTRIPLE* colour, const char* framebuffer) {
#ifdef RPI
	display_sense_ledgrid(colour, framebuffer);
#endif // RPI
}

void clear_ledgrid() {
#ifdef RPI
	clear_sense_ledgrid();
#endif // RPI
}

void build_one_color(SPGM_RGBTRIPLE colour) {
#ifdef RPI
	build_one_color_sense(colour);
#endif // RPI
}

void build_rainbow() {
#ifdef RPI
	build_rainbow_sense();
#endif // RPI
}