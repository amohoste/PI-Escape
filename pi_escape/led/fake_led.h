#ifndef RPI
#ifndef _FAKE_LED_H
#define _FAKE_LED_H

// Use extern "C" so led.c can call these c++ functions
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include "../../util/rgb_triple.h"

// Bitmap headers:
//////////////////

// as we can use microsofts gdi on linux we'll define the right struct here ourselves
// sadly de defining the fileheader will give us a struct with size 16 instead of 14, 
// resulting in padding and subsequently an unreadable bmp file. We'll have to write those 14 bits ourselves.

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

typedef struct tagBITMAPINFOHEADER {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

// Functions used by led.c functions:
/////////////////////////////////////

// Create an empty square
EXTERNC void clear_fake_ledgrid();

// Create one color square
EXTERNC void build_one_color_fake(SPGM_RGBTRIPLE);

// Create rainbow square
EXTERNC void build_rainbow_fake();

// Create square corresponding to the given array of colours
EXTERNC void build_array_fake(SPGM_RGBTRIPLE**);
#endif // _FAKE_LED_H
#endif // !RPI
