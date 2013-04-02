#include "screen.h"
#include "utils.h"
#include "dma.h"
static u16 *video_buffer = (u16 *)0x6000000;
#define PIXEL_ADDR_OF(row, col) (video_buffer + (row) * SCREEN_WIDTH + (col))
#define PIXEL_OF(row, col) (*PIXEL_ADDR_OF((row), (col)))
//static void fill_row(int row, int start, int end, u16 color);
static void fill_row_dma(int row, int start, int end, u16 color);

void set_pixel(int r, int c, u16 color) 
{
  PIXEL_OF(r, c) = color; 
}

void fill_frame(Frame *bounds, u16 color) 
{
  for(int i = bounds->top; i <= bounds->top + bounds->height; i++) 
  {
    fill_row_dma(i, bounds->left, bounds->width, color);
  }
}
/*
void fill_row(int row, int start_col, int width, u16 color)
{
    for(int j = start_col; j <= start_col + width; j++)
    {
      set_pixel(row, j, color);
    }
}*/

void fill_row_dma(int row, int start_col, int width, volatile u16 color)
{
  DMA[3].src = &color;
  DMA[3].dst = PIXEL_ADDR_OF(row, start_col);
  DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | width;
}

void erase_frame(Frame *bounds, u16 bg_color)
{
  fill_frame(bounds, bg_color);
}

void translate_vert(Frame* bounds, int pixels)
{
  if(pixels == 0)
  {
    return;
  }
  Frame old_replaced = {bounds->left, pixels > 0 ? bounds->top : bounds->top + bounds->height + pixels,  bounds->width, ABS(pixels)};
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
  fill_frame(&old_replaced, BLACK);
  fill_frame(bounds, WHITE);
}

void translate_horiz(Frame *bounds, int pixels)
{
  if(pixels == 0)
  {
    return;
  }
  Frame old_replaced = { pixels > 0 ? bounds->left : bounds->left + pixels, bounds->top, ABS(pixels), bounds->height};
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
  fill_frame(&old_replaced, BLACK);
  fill_frame(bounds, WHITE);
}

int off_screen(Frame *bounds)
{
  return (bounds->top < 0) || (bounds->left < 0)
    || (bounds->top + bounds->height > SCREEN_HEIGHT)
    || (bounds->left + bounds->width > SCREEN_WIDTH);
}


static int in_bounds(Frame *bounds, int row, int column);

int in_bounds(Frame *bounds, int row, int column)
{
  return ( bounds->left <= column ) && (column <= bounds->left + bounds->width)
    && (bounds->top <= row) && (row <= bounds->top + bounds->height);
}

int intersect(Frame *a, Frame *b)
{
  
  return in_bounds(a, b->top, b->left) ||
    in_bounds(a, b->top, b->left + b->width) ||
    in_bounds(a, b->top + b->height, b->left) ||
    in_bounds(a, b->top + b->height, b->left + b->width);
}
void set_background(u16 *source)
{
  wait_for_vblank();
  DMA[3].src = source;
  DMA[3].dst = PIXEL_ADDR_OF(0,0);
  DMA[3].cnt = DMA_ON | DMA_SOURCE_INCREMENT | ( SCREEN_WIDTH * SCREEN_HEIGHT );
 
}

void draw_picture(u16 *source, Frame *frame)
{
  
}

void wait_for_vblank()
{
  while(SCANLINE_COUNTER > 160);//wait for it to go back to beginning
  while(SCANLINE_COUNTER < 160);//after 160 we are good to go
}
