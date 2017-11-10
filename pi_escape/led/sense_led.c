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

// name is RPI
// filesize is 192

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char* framebuffer) {
	int ledgridFile;
	uint16_t *mapping;
	uint16_t *pointer;
	struct fb_var_screeninfo device_info;
	if ((ledgridFile = open(framebuffer, O_RDWR)) == -1) {
		return;
	}
	if (ioctl(ledgridFile, FBIOGET_VSCREENINFO, &device_info) == -1) {
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
}

void display_ledgrid_fb1(SPGM_RGBTRIPLE* ledgrid) {
	display_ledgrid(ledgrid, FRAMEBUFFER);
}

void clear_ledgrid() {
	SPGM_RGBTRIPLE ledgrid[64];
	for (int i = 0; i <= 64; i++)
	{
		SPGM_RGBTRIPLE current;
		current.rgbRed = 0;
		current.rgbGreen = 0;
		current.rgbBlue = 0;
		ledgrid[i] = current;
	}
	display_ledgrid_fb1(ledgrid);
}

#endif // RPI