#ifndef _SENSE_LED_H
#define _SENSE_LED_H
#ifdef RPI


#include "../../util/rgb_triple.h"

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid,
                     const char* framebuffer);


void clear_ledgrid();

void build_one_color(SPGM_RGBTRIPLE color);

void build_rainbow();
#endif
#endif	