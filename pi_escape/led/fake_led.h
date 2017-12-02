#ifndef _FAKE_LED_H
#define _FAKE_LED_H

// Use extern "C" so led.c can call these c++ functions
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include "../../util/rgb_triple.h"

// Write bitmap to bmp file
void display_fake_ledgrid(SPGM_RGBTRIPLE*, const char*);

// Create an empty square
EXTERNC void clear_fake_ledgrid();

// Create one color square
EXTERNC void build_one_color_fake(SPGM_RGBTRIPLE);

// Create rainbow square
EXTERNC void build_rainbow_fake();

// Create square corresponding to the given array of colours
EXTERNC void build_array_fake(SPGM_RGBTRIPLE**);
#endif
