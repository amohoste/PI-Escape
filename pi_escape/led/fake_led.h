#ifndef _FAKE_LED_H
#define _FAKE_LED_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


#include "../../util/rgb_triple.h"

EXTERNC void display_fake_ledgrid(SPGM_RGBTRIPLE*, const char*);

EXTERNC void clear_fake_ledgrid();

EXTERNC void build_one_color_fake(SPGM_RGBTRIPLE);

EXTERNC void build_rainbow_fake();

#endif
