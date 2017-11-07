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

// name is RPI
// filesize is 192

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char* framebuffer) {
	int file;
	uint16_t *mapping;
	uint16_t *pointer;
	struct fb_fix_screeninfo device_info;
	if ((file = open(framebuffer, O_RDWR)) == -1) {
		return;
	}
	/*
	if (ioctl(file, FBIOGET_FSCREENINFO, device_info) == -1) {
		close(file);
		return;
	}
	*/
	mapping = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
	if (mapping == MAP_FAILED) {
		close(file);
		return;
	}

	pointer = mapping;
	memset(mapping, 0, FILESIZE);
	for (int i = 0; i < LENGTH_BUFFER; i++) {
		SPGM_RGBTRIPLE rgb = ledgrid[i];
		*(pointer + i) = rgb.rgbRed << 11 | rgb.rgbGreen << 5 | rgb.rgbBlue;
	}
}
#endif // RPI