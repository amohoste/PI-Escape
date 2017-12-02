#ifndef _FAKE_LED_H
#define _FAKE_LED_H

#include "../../util/rgb_triple.h"

void display_fake_ledgrid(SPGM_RGBTRIPLE*, const char*);

void clear_fake_ledgrid();

void build_one_color_fake(SPGM_RGBTRIPLE);

void build_rainbow_fake();

#endif
