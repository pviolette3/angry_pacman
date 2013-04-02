#ifndef __SCREEN_H__
#define __SCREEN_H__

#define SCREEN_WIDTH (240)
#define SCREEN_HEIGHT (160)
#define RGB(r, g, b) ((r) | ((g) << 5) | ((b) << 10))
#define REG_DISPCNT (*((u16*) (0x4000000)))
#define MODE3 (3)
#define VIDEO_MODE (1 << 10)
#define SCANLINE_COUNTER (*(u16*) (0x4000006))

#define WHITE (RGB(31,31,31))
#define BLACK (RGB(0, 0, 0))
#define YELLOW (RGB(31, 31, 0))
#define RED (RGB(31,0,0))
#define BLUE (RGB(0,0,31))
#define GREEN (RGB(0,31,0))

typedef unsigned short u16;

typedef struct {
  int top;
  int left;
  int width;
  int height;
} Frame;

/*
 * Sets the pixel at (r,c) to the specified color
 */
void set_pixel(int r, int c, u16 color);

void translate_vert(Frame *bounds, int pixels);
void translate_horiz(Frame *bounds, int pixels);
/*
 * Fill the given frame with the given color
 *
 */
void fill_frame(Frame *bounds, u16 color);
void erase_frame(Frame *bounds, u16 color);
int off_screen(Frame *bounds);

int intersect(Frame *a, Frame *b);
void wait_for_vblank();

void set_background(u16 *source);
void draw_picture(u16 *source, Frame *frame);

#endif
