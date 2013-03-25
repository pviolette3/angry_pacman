#include "screen.h"

u16 *video_buffer = (u16 *) 0x6000000;

void set_pixel(int r, int c, u16 color) 
{
 video_buffer[c * SCREEN_WIDTH + r] = color; 
}

void fill_frame(frame bounds, u16 color) 
{
  for(int i = bounds.top; i <= bounds.top + bounds.height; i++) 
  {
    for(int j = bounds.left; j <= bounds.left + bounds.width; j++) 
    {
      set_pixel(j, i, color);
    }
  }
}

void translate_vert(frame* bounds, int pixels)
{
  if(pixels == 0)
  {
    return;
  }
  frame old_replaced = {pixels > 0 ? bounds->top : bounds->top + bounds->height + pixels, bounds->left, pixels > 0 ? pixels : -pixels, bounds->width};
  bounds->top += pixels;
  //here, we don't move if there's no more to translate
  if(bounds->top <= 0) 
  {
    bounds->top = 0;
    return;
  }
  if(bounds->top + bounds->height >= SCREEN_HEIGHT)
  {
    bounds->top =  SCREEN_HEIGHT - bounds-> height;
    return;
  }
  fill_frame(old_replaced, BLACK);
  fill_frame(*bounds, WHITE);
}

void translate_horiz(frame* bounds, int pixels)
{
  if(pixels == 0)
  {
    return;
  }
  frame old_replaced = {bounds->top, pixels > 0 ? bounds->left : bounds->left + pixels, bounds->height, pixels > 0 ? pixels : -pixels};
  bounds->left += pixels;
  //here, we don't move if there's no more to translate
  if(bounds->left <= 0) 
  {
    bounds->left = 0;
    return;
  }
  if(bounds->left + bounds->width >= SCREEN_WIDTH)
  {
    bounds->left =  SCREEN_WIDTH - bounds->width;
    return;
  }
  fill_frame(old_replaced, BLACK);
  fill_frame(*bounds, WHITE);
}


void wait_for_vblank()
{
  while(SCANLINE_COUNTER > 160);//wait for it to go back to beginning
  while(SCANLINE_COUNTER < 160);//after 160 we are good to go
}
