#ifndef LED_H
#define LED_H

#include "../../util/rgb_triple.h"

#ifdef RPI
#include "sense_led.h"
#endif // RPI
#ifndef RPI
#include "fake_led.h"
#endif // !RPI

// TODO add 2d array support

void display_ledgrid(SPGM_RGBTRIPLE*, const char*);

void clear_ledgrid();

void build_one_color(SPGM_RGBTRIPLE);

void build_rainbow();

#endif