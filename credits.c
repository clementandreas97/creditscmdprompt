#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <math.h>

int xResolution;
int yResolution;

int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
int x = 0, y = 0;
int t = 0;
long int location = 0;

// Draw point

void setPixel(int x, int y, int c1, int c2, int c3) {
    location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
    *(fbp + location) = c1;
    *(fbp + location + 1) = c2;
    *(fbp + location + 2) = c3;
}

// Draw line

void bresenhamLow(int x0, int y0, int x1, int y1, int c1, int c2, int c3) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = 2*dy - dx;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        setPixel(x,y,c1,c2,c3);
        if (D > 0) {
            y += yi;
            D -= 2*dx;
        }
        D += 2*dy;
    }
}

void bresenhamHigh(int x0, int y0, int x1, int y1, int c1, int c2, int c3) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = 2*dx - dy;
    int x = x0;
    for (int y = y0; y <= y1; y++) {
        setPixel(x,y,c1,c2,c3);
        if (D > 0) {
            x += xi;
            D -= 2*dy;
        }
        D += 2*dx;
    }
}

void bresenham(int x0, int y0, int x1, int y1, int c1, int c2, int c3) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 > x1) {
            bresenhamLow(x1,y1,x0,y0,c1,c2,c3);
        }
        else {
            bresenhamLow(x0,y0,x1,y1,c1,c2,c3);
        }
    }
    else {
        if (y0 > y1) {
            bresenhamHigh(x1,y1,x0,y0,c1,c2,c3);
        }
        else {
            bresenhamHigh(x0,y0,x1,y1,c1,c2,c3);
        }
    }
}

// Draw shape

void drawShape(char *fileName, int c1, int c2, int c3) {
	// Read file
	FILE *f = fopen(fileName, "r");
	char c;
	if (f == NULL) {
		return;
	}
	// Read first point
	int x0 = 0;
	int y0 = 0;
	while (c != '(') {
		c = fgetc(f);
	}
	while ((c = fgetc(f)) != ',') {
		x0 = x0*10 + (c - '0');
	}
	while ((c = fgetc(f)) != ')') {
		y0 = y0*10 + (c - '0');
	}
	c = fgetc(f);
	// Read all another points
	int x1 = x0;
	int y1 = y0;
	int x2 = 0;
	int y2 = 0;
	while (c != '}') {
		while (c != '(') {
			c = fgetc(f);
		}
		while ((c = fgetc(f)) != ',') {
			x2 = x2*10 + (c - '0');
		}
		while ((c = fgetc(f)) != ')') {
			y2 = y2*10 + (c - '0');
		}
		bresenham(x1,y1,x2,y2,c1,c2,c3);
		x1 = x2;
		y1 = y2;
		x2 = 0;
		y2 = 0;
		c = fgetc(f);
	}

	bresenham(x1,y1,x0,y0,c1,c2,c3);
	fclose(f);
}

// Flood fill


int isSameColor(int x0, int y0, int c11, int c12, int c13) {
	int loc = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
	int c01 = *(fbp + loc);
	if (c01 < 0) {
		c01 += 256;
	}
	int c02 = *(fbp + loc + 1);
	if (c02 < 0) {
		c02 += 256;
	}
	int c03 = *(fbp + loc + 2);
	if (c03 < 0) {
		c03 += 256;
	}
	return (c01 == c11 && c02 == c12 && c03 == c13);
}

void floodFill(int x0, int y0, int c1, int c2, int c3) {
	if (isSameColor(x0,y0,c1,c2,c3)) {
		return;
	}
	else {
		setPixel(x0,y0,c1,c2,c3);
		floodFill(x0+1,y0,c1,c2,c3);
		floodFill(x0-1,y0,c1,c2,c3);
		floodFill(x0,y0+1,c1,c2,c3);
		floodFill(x0,y0-1,c1,c2,c3);
	}
}

void colorShape(char *fileName, int c1, int c2, int c3) {
	// Read file
	FILE *f = fopen(fileName, "r");
	char c;
	if (f == NULL) {
		return;
	}
	// Skip points
	while (c != '}') {
		c = fgetc(f);
	}
	while (c != '{') {
		c = fgetc(f);
	}
	// Read triangles
	int x0 = 0;
	int y0 = 0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	while (c != EOF) {
		if (c == '{') {
			// Triangle 1
			while (c != '(') {
				c = fgetc(f);
			}
			while ((c = fgetc(f)) != ',') {
				x0 = x0*10 + (c - '0');
			}
			while ((c = fgetc(f)) != ')') {
				y0 = y0*10 + (c - '0');
			}
			c = fgetc(f);
			// Triangle 2
			while (c != '(') {
				c = fgetc(f);
			}
			while ((c = fgetc(f)) != ',') {
				x1 = x1*10 + (c - '0');
			}
			while ((c = fgetc(f)) != ')') {
				y1 = y1*10 + (c - '0');
			}
			c = fgetc(f);
			// Triangle 3
			while (c != '(') {
				c = fgetc(f);
			}
			while ((c = fgetc(f)) != ',') {
				x2 = x2*10 + (c - '0');
			}
			while ((c = fgetc(f)) != ')') {
				y2 = y2*10 + (c - '0');
			}
			c = fgetc(f);
			// Color
			bresenham(x0,y0,x1,y1,c1,c2,c3);
			bresenham(x1,y1,x2,y2,c1,c2,c3);
			bresenham(x2,y2,x0,y0,c1,c2,c3);
			int centroidX = round((float)(x0+x1+x2)/(float)3);
			int centroidY = round((float)(y0+y1+y2)/(float)3);
			floodFill(centroidX,centroidY,c1,c2,c3);
			x0 = 0;
			y0 = 0;
			x1 = 0;
			y1 = 0;
			x2 = 0;
			y2 = 0;
		}
		else {
			c = fgetc(f);
		}
	}

	fclose(f);
}

// Main

int main(int argc, char **argv) {
    // Input resolution
    if (argc != 7) {
        fprintf(stderr, "Please input filename, resolution, red, green, and blue\n");
        fprintf(stderr, "Example: %s input.txt 1366 768 255 255 255\n", argv[0]);
        return -1;
    }
    char *fileName = argv[1];
    xResolution = atoi(argv[2]);
    yResolution = atoi(argv[3]);
    int red = atoi(argv[4]);
    int green = atoi(argv[5]);
    int blue = atoi(argv[6]);

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                        fbfd, 0);
    if ((long)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    // Figure out where in memory to put the pixel
    drawShape(fileName, blue, green, red);
    colorShape(fileName, blue, green, red);

    munmap(fbp, screensize);
    sleep(5);
    close(fbfd);
    return 0;
 }
