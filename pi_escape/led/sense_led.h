#ifdef RPI
#ifndef _SENSE_LED_H
#define _SENSE_LED_H

#include "../../util/rgb_triple.h"

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid,
                     const char* framebuffer);

// aangezien de framebuffer altijd /dev/fb1 is
void display_ledgrid_fb1(SPGM_RGBTRIPLE* ledgrid);

void clear_ledgrid();

#endif
#endif	