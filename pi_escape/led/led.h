#ifndef LED_H
#define LED_H

#include "../../util/rgb_triple.h"

#define GRIDSIZE 8

#ifdef RPI
#include "sense_led.h"
#endif // RPI
#ifndef RPI
#include "fake_led.h"
#endif // !RPI

// TODO add 2d array support

// Show an empty square
void clear_ledgrid();

// Show one color square
void build_one_color(SPGM_RGBTRIPLE);

// Show rainbow square
void build_rainbow();

// Show square corresponding to the given array of colours
void build_array(SPGM_RGBTRIPLE**);
#endif