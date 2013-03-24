#include "screen.h"

u16 *video_buffer = (u16 *) 0x6000000;

void set_pixel(int r, int c, u16 color) {
 video_buffer[c * SCREEN_WIDTH + r] = color; 
}

void fill_frame(frame bounds, u16 color) {
  for(int i = bounds.c; i <= bounds.c + bounds.height; i++) {
    for(int j = bounds.c; j <= bounds.c + width; j++) {
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
