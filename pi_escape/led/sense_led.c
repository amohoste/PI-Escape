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

int pixels[64][3] = [
	[255, 0, 0], [255, 0, 0], [255, 87, 0], [255, 196, 0], [205, 255, 0], [95, 255, 0], [0, 255, 13], [0, 255, 122],
		[255, 0, 0], [255, 96, 0], [255, 205, 0], [196, 255, 0], [87, 255, 0], [0, 255, 22], [0, 255, 131], [0, 255, 240],
		[255, 105, 0], [255, 214, 0], [187, 255, 0], [78, 255, 0], [0, 255, 30], [0, 255, 140], [0, 255, 248], [0, 152, 255],
		[255, 223, 0], [178, 255, 0], [70, 255, 0], [0, 255, 40], [0, 255, 148], [0, 253, 255], [0, 144, 255], [0, 34, 255],
		[170, 255, 0], [61, 255, 0], [0, 255, 48], [0, 255, 157], [0, 243, 255], [0, 134, 255], [0, 26, 255], [83, 0, 255],
		[52, 255, 0], [0, 255, 57], [0, 255, 166], [0, 235, 255], [0, 126, 255], [0, 17, 255], [92, 0, 255], [201, 0, 255],
		[0, 255, 66], [0, 255, 174], [0, 226, 255], [0, 117, 255], [0, 8, 255], [100, 0, 255], [210, 0, 255], [255, 0, 192],
		[0, 255, 183], [0, 217, 255], [0, 109, 255], [0, 0, 255], [110, 0, 255], [218, 0, 255], [255, 0, 183], [255, 0, 74]
]

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char* framebuffer) {
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

void display_ledgrid_fb1(SPGM_RGBTRIPLE* ledgrid) {
	display_ledgrid(ledgrid, FRAMEBUFFER);
}

void clear_ledgrid() {
	display_ledgrid_fb1(build_one_color(0));
}

SPGM_RGBTRIPLE* build_one_color(int color) {
	SPGM_RGBTRIPLE ledgrid[64];
	for (int i = 0; i < 64; i++)
	{
		ledgrid[i] = (SPGM_RGBTRIPLE) { .rgbRed = color, .rgbGreen = color, .rgbBlue = color };
	}
	return ledgrid;
}

SPGM_RGBTRIPLE* build_rainbow() {
	SPGM_RGBTRIPLE ledgrid[64];
	for (int i = 0; i < 64; i++)
	{
		ledgrid[i] = (SPGM_RGBTRIPLE) { .rgbRed = pixel[i][0], .rgbGreen = pixel[i][0], .rgbBlue = pixel[i][0]};
	}
	return ledgrid;
}
#endif // RPI