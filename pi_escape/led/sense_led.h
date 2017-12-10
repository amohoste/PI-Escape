#ifndef _SENSE_LED_H
#define _SENSE_LED_H
#ifdef RPI

#include "../../util/rgb_triple.h"
#include "led.h"

void display_sense_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char* framebuffer);

void clear_sense_ledgrid();

void build_one_color_sense(SPGM_RGBTRIPLE color);

void build_rainbow_sense();

void build_array_sense(SPGM_RGBTRIPLE** square);
#endif // RPI
#endif // _SENSE_LED_H