#ifndef LED_H
#define LED_H

#include "../../util/rgb_triple.h"
#include "fake_led.h"
#include "sense_led.h"

// TODO add 2d array support

void display_ledgrid(SPGM_RGBTRIPLE*, const char*);

void clear_ledgrid();

void build_one_color(SPGM_RGBTRIPLE);

void build_rainbow();

#endif