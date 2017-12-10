#ifdef RPI

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "sense_led.h"

#define LENGTH_BUFFER 64
#define FILESIZE (LENGTH_BUFFER * sizeof(SPGM_RGBTRIPLE))
#define FRAMEBUFFER "/dev/fb1"

// hardcode rainbow colors
int rainbow[LENGTH_BUFFER][3] = {
	{ 255,   0,   0 },{ 255, 128,   0 },{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{   0, 255,   0 },{   0, 255, 128 },{   0, 255, 255 },
	{ 255, 128,   0 },{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{   0, 255,   0 },{   0, 255, 128 },{   0, 255, 255 },{   0, 191, 255 },
	{ 255, 153,   0 },{ 255, 191,   0 },{ 255, 255,   0 },{   0, 255,   0 },{   0, 255, 128 },{   0, 255, 255 },{   0, 191, 255 },{   0, 104, 255 },
	{ 255, 191,   0 },{ 255, 255,   0 },{   0, 255,   0 },{   0, 255, 128 },{   0, 255, 255 },{   0, 191, 255 },{   0, 104, 255 },{  64,   0, 255 },
	{ 255, 255,   0 },{   0, 255,   0 },{   0, 255, 128 },{   0, 255, 255 },{   0, 191, 255 },{   0, 104, 255 },{  64,   0, 255 },{ 128,   0, 255 },
	{   0, 255,   0 },{   0, 255, 128 },{   0, 255, 255 },{   0, 191, 255 },{   0, 104, 255 },{  64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },
	{   0, 255, 128 },{   0, 255, 255 },{   0, 191, 255 },{   0, 104, 255 },{  64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },{ 255,   0,  64 },
	{   0, 255, 255 },{   0, 191, 255 },{   0, 104, 255 },{  64,   0, 255 },{ 128,   0, 255 },{ 255,   0, 191 },{ 255,   0,  64 },{ 255,   0,   0 }
};


void display_sense_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char* framebuffer) {
	int ledgridFile;
	uint16_t *mapping;
	uint16_t *pointer;
	struct fb_fix_screeninfo device_info;
	if ((ledgridFile = open(framebuffer, O_RDWR)) == -1) {
		return;
	}
	if (ioctl(ledgridFile, FBIOGET_FSCREENINFO, &device_info) == -1) {
		close(ledgridFile);
		return;
	}

	mapping = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, ledgridFile, 0);
	if (mapping == MAP_FAILED) {
		close(ledgridFile);
		return;
	}

	pointer = mapping;
	for (int i = 0; i < LENGTH_BUFFER; i++) {
		SPGM_RGBTRIPLE rgb = ledgrid[i];
		*(pointer + i) = rgb.rgbRed << 11 | rgb.rgbGreen << 5 | rgb.rgbBlue;
	}
	close(ledgridFile);
}

void clear_sense_ledgrid() {
	build_one_color((SPGM_RGBTRIPLE) { .rgbRed = 0, .rgbGreen = 0, .rgbBlue = 0 });
}

void build_one_color_sense(SPGM_RGBTRIPLE color) {
	SPGM_RGBTRIPLE ledgrid[LENGTH_BUFFER];
	for (int i = 0; i < LENGTH_BUFFER; i++)
	{
		ledgrid[i] = (SPGM_RGBTRIPLE) { .rgbRed = color.rgbRed, .rgbGreen = color.rgbGreen, .rgbBlue = color.rgbBlue};
	}
	display_sense_ledgrid(ledgrid, FRAMEBUFFER);
}

void build_rainbow_sense() {
	SPGM_RGBTRIPLE ledgrid[LENGTH_BUFFER];
	for (int i = 0; i < LENGTH_BUFFER; i++)
	{
		ledgrid[i] = (SPGM_RGBTRIPLE) { .rgbRed = rainbow[i][0], .rgbGreen = rainbow[i][1], .rgbBlue = rainbow[i][2] };
	}
	display_sense_ledgrid(ledgrid, FRAMEBUFFER);
}

void build_array_sense(SPGM_RGBTRIPLE** square) {
	SPGM_RGBTRIPLE ledgrid[LENGTH_BUFFER];
	int c = 0;
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			ledgrid[c] = square[i][j];
			c++;
		}
	}
	display_sense_ledgrid(ledgrid, FRAMEBUFFER);
}
#endif // RPI