#ifdef RPI
#ifndef _SENSE_LED_H
#define _SENSE_LED_H

#include "../../util/rgb_triple.h"

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid,
                     const char* framebuffer);

unsigned long rgbTOhex(int, int, int);

#endif
#endif	