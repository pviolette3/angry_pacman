#include "mylib.h"
u16 *videoBuffer = (u16 *) 0x6000000;

void set_pixel(int r, int c, u16 color) {
 videoBuffer[c * SCREEN_WIDTH + r] = color; 
}

void draw_rect(int r, int c, int width, int height, u16 color) {
  
  for(int i = c; i <= c + height; i++) {
    for(int j = c; j <= c + width; j++) {
      set_pixel(i, j, color);
    }
  }
}

void delay(int n) {
  volatile int x = 1000*n;
  for(; x >= 0; x--) {
    x ++;
    x --;
    //delay !
  }
}
