#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
int x = 0, y = 0;
int t = 0;
long int location = 0;

// ALPHABETS

void drawSpace(int x0, int y0, int d, int c, int b){
    
}

void draw3(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        
         location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
        (y+vinfo.yoffset) * finfo.line_length;
                        
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        
        x++;

        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
        (y+vinfo.yoffset) * finfo.line_length;
                        
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
    }

}

void drawA(int x0, int y0, int d, int c, int b, int c1, int c2){
    int y = y0 + b;
    int mid = x0+d/2;
    
    int y_for_mid = y0 + b + d/2;
    
    for(int x_for_mid = x0 + d/4; x_for_mid<=(x0 + 3*d/4); x_for_mid++){
        location = (x_for_mid+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y_for_mid+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
    }
    
    for (int x = x0+d/2; x >= x0; x--) {
        
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+2*(mid-x)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        y++;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+2*(mid-x)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        y++;
    }
    
    y_for_mid = y0 + d/2;
    for(int x_for_mid = x0 + d/4; x_for_mid<=(x0 + 3*d/4); x_for_mid++){
        location = (x_for_mid+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y_for_mid+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
    }

    y = y0;
    for (int x = x0+d/2; x >= x0; x--) {
        
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;

        location = (x+2*(mid-x)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;

        y++;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+2*(mid-x)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        y++;
    }
}

void drawB(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        
         location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
        (y+vinfo.yoffset) * finfo.line_length;
                        
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        x++;

        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
        (y+vinfo.yoffset) * finfo.line_length;
                        
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
    }

}

void drawC(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        x++;

    }

}

void drawD(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        if (y >= y0 + d/2) {
            location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+b+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        }

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        if (x <= x0 + d/2) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        }

        x++;

    }
    x = x0 + d/2;
    for (int y = y0+b; y<= y0 + d/2+b; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;
    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        if (y >= y0 + d/2) {
            location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        }

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        if (x <= x0 + d/2) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        }

        x++;

    }

    x = x0 + d/2;
    for (int y = y0; y<= y0 + d/2; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        
        x++;
    }


}

void drawE(int x0, int y0, int d, int c, int b, int c1, int c2) {
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
    }

    y = y0 + b; 
    for (int x = x0; x <= x0+d; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+d/3+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
    }

    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;    }

    for (int x = x0; x <= x0+d; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d/3+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;    }

}

void drawI(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0 + d/2;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
    }

    for (int x = x0+d/2-d/4; x <= x0+d/2+d/4; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
    }

    for (int y = y0; y <= y0+d; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;    }

    for (int x = x0+d/2-d/4; x <= x0+d/2+d/4; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;    }
}

void drawK(int x0, int y0, int d, int c, int b, int c1, int c2) {

    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

    }

    y = y0+b;
    for (int x = x0+d; x >= x0; x--) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d-(y-b-y0)+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        x--;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d-(y-b-y0)+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        y++;

    }

    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
    }

    y = y0;
    for (int x = x0+d; x >= x0; x--) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d-(y-y0)+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        x--;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d-(y-y0)+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        y++;

    }

}

void drawL(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        x++;

    }

}

void drawM(int x0, int y0, int d, int c, int b, int c1, int c2) {
    int y = y0 + b;
    for (int x = x0; x <= x0+d/4; x++) {
        for (int i = 0; i<=3; i++) {
            location = (x0+d/4-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            location = (x0+d/2+d/4-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            location = (x+d/4+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            location = (x+d/2+d/4+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            y++;
        }

    }

    y = y0;
    for (int x = x0; x <= x0+d/4; x++) {
        for (int i = 0; i<=3; i++) {
            location = (x0+d/4-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            location = (x0+d/2+d/4-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            location = (x+d/4+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            location = (x+d/2+d/4+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            y++;
        }
        
    }
}

void drawN(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;
    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        x++;
    }

}

void drawO(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
        (y+vinfo.yoffset) * finfo.line_length;
                        
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        x++;

       
        location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
        (y+vinfo.yoffset) * finfo.line_length;
                        
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
    }

}

void drawP(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

        if (y <= y0+b + d/2) {
            location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        }

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        x++;

        if (y <= y0 + d/2) {
            location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = c2;
            *(fbp + location + 1) = c1;
            *(fbp + location + 2) = c;        
        }

    }

}

void drawR(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        x++;

        if (y <= y0+b + d/2) {
            location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        }

    }

    y = y0+b;
    for (int x = x0+d; x >= x0; x--) {
        x--;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d-(y-b-y0)+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        y++;

    }

    x = x0;
    for (int y = y0; y <= y0+d; y++) {
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d/2+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        x++;

        if (y <= y0 + d/2) {
            location = (x0+d+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;        }

    }

    y = y0;
    for (int x = x0+d; x >= x0; x--) {
        x--;

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+d-(y-y0)+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        y++;

    }

}

void drawT(int x0, int y0, int d, int c, int b, int c1, int c2) {
    x = x0 + d/2;
    for (int y = y0+b; y <= y0+d+b; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
    }

    for (int x = x0; x <= x0+d; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+b+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

    }

    for (int y = y0; y <= y0+d; y++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;    }

    for (int x = x0; x <= x0+d; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y0+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
    }
}

void drawV(int x0, int y0, int d, int c, int b, int c1, int c2) {
    int y = y0 + b;
    for (int x = x0; x <= x0+d/2; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x0+d-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        y++;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        location = (x0+d-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

        y++;
    }

    y = y0;
    for (int x = x0; x <= x0+d/2; x++) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x0+d-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        y++;
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        location = (x0+d-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
            (y+vinfo.yoffset) * finfo.line_length;
                            
        *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
        y++;
    }
}

void drawW(int x0, int y0, int d, int c, int b, int c1, int c2) {
    int y = y0 + b;
    for (int x = x0; x <= x0+d/4; x++) {
        for (int i = 0; i<=3; i++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            location = (x+d/2+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            location = (x0+d-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            location = (x0+d/2-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;

            y++;
        }

    }

    y = y0;
    for (int x = x0; x <= x0+d/4; x++) {
        for (int i = 0; i<=3; i++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            location = (x+d/2+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            location = (x0+d-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            location = (x0+d/2-(x-x0)+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                                
            *(fbp + location) = c2;
        *(fbp + location + 1) = c1;
        *(fbp + location + 2) = c;
            y++;
        }
        
    }
}

// ERASE

void eraseScreen() {
    for (int x = 0; x < vinfo.xres-6; x++) {
        for (int y = 0; y < vinfo.yres-6; y++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + 
                (y+vinfo.yoffset) * finfo.line_length;
                            
            *(fbp + location) = 0;
        *(fbp + location + 1) = 0;
        *(fbp + location + 2) = 0;
        }
    }
}

// MAIN

 int main()
 {
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
     if ((int)fbp == -1) {
         perror("Error: failed to map framebuffer device to memory");
         exit(4);
     }
     printf("The framebuffer device was mapped to memory successfully.\n");

     //x = 300; y = 100;       // Where we are going to put the pixel

     // Figure out where in memory to put the pixel
     for(t = 0; t<650; t+=1){
		  drawK(600,650-t,50,255,1,7,168);
          drawE(660,650-t,50,255,1,7,168);
          drawL(720,650-t,50,255,1,7,168);
          drawO(780,650-t,50,255,1,7,168);
          drawM(840,650-t,50,255,1,7,168);
          drawP(900,650-t,50,255,1,7,168);
          drawO(960,650-t,50,255,1,7,168);
          drawK(1020,650-t,50,255,1,7,168);
          // drawSpace(1080,650-t,50,209,1,166,180);
          draw3(1140,650-t,50,255,1,7,168);

          drawT(600,730-t,50,226,1,114,15);
          drawR(660,730-t,50,226,1,114,15);
          drawE(720,730-t,50,226,1,114,15);
          drawV(780,730-t,50,226,1,114,15);
          drawI(840,730-t,50,226,1,114,15); 
          drawN(900,730-t,50,226,1,114,15); 

          drawE(600,790-t,50,17,1,187,214);
          drawD(660,790-t,50,17,1,187,214);
          drawW(720,790-t,50,17,1,187,214);
          drawI(780,790-t,50,17,1,187,214);
          drawN(840,790-t,50,17,1,187,214); 
          
          drawA(600,850-t,50,214,1,17,17);
          drawL(660,850-t,50,214,1,17,17);
          drawV(720,850-t,50,214,1,17,17);
          drawI(780,850-t,50,214,1,17,17);
          drawN(840,850-t,50,214,1,17,17); 

          drawA(600,910-t,50,247,1,232,22);
          drawL(660,910-t,50,247,1,232,22);
          drawB(720,910-t,50,247,1,232,22);
          drawE(780,910-t,50,247,1,232,22);
          drawR(840,910-t,50,247,1,232,22); 
          drawT(900,910-t,50,247,1,232,22);

          drawM(1080,730-t,50,82,1,226,15);
          drawI(1140,730-t,50,82,1,226,15);
          drawK(1200,730-t,50,82,1,226,15);
          drawE(1260,730-t,50,82,1,226,15);

          drawC(1080,790-t,50,255,1,255,255);
          drawL(1140,790-t,50,255,1,255,255);
          drawE(1200,790-t,50,255,1,255,255);
          drawM(1260,790-t,50,255,1,255,255);
          drawE(1320,790-t,50,255,1,255,255); 
          drawN(1380,790-t,50,255,1,255,255);
          drawT(1440,790-t,50,255,1,255,255);

          drawK(1080,850-t,50,124,1,10,255);
          drawE(1140,850-t,50,124,1,10,255);
          drawV(1200,850-t,50,124,1,10,255);
          drawI(1260,850-t,50,124,1,10,255);
          drawN(1320,850-t,50,124,1,10,255); 

          usleep(10000);
	}
     munmap(fbp, screensize);
     sleep(5);
     close(fbfd);
     return 0;
 }
