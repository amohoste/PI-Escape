#ifdef RPI

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "sense_led.h"

#define LENGTH_BUFFER 64
#define FILESIZE (NUM_WORDS * sizeof(uint16_t))
#define RGB565_RED 0xF800

void display_ledgrid(SPGM_RGBTRIPLE* ledgrid, const char* framebuffer) {
	//array altijd 64 lang
	int file;
	struct fb_fix_screeninfo device_info;
	if ((file = open(framebuffer, O_RDWR)) == -1) {
		return -1;
	}
	if (ioctl(file, FBIOGET_FSCREENINFO, device_info) == -1) {
		close(file);
		return -1;
	}
	printf("%s", device_info.id); // to see the real name
	if (device_info.id != "RPi-Sense FB") {
		close(file);
		return -1;
	}
	map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
	if (map == MAP_FAILED) {
		close(file);
		return -1;
	}

	/* set a pointer to the start of the memory area */
	p = map;

	/* clear the led matrix */
	memset(map, 0, FILESIZE);

	/* light it up! */
	for (i = 0; i < LENGTH_BUFFER; i++) {
		*(p + i) = RGB565_RED;
		usleep(2500);
	}
	memset(map, 0, FILESIZE);
	return 0;
}
#endif // RPI