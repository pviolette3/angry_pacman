#define SCREEN_WIDTH (240)
#define SCREEN_HEIGHT (160)
#define RGB(r, g, b) ((r) + ((g) << 5) + ((b) << 10))
#define REG_DISPCNT (*((u16*) (0x4000000)))
#define MODE ((1 << 10) | 3 )//Set 10th bit (video mode)) and mode 3
#define BLACK (RGB(0, 0, 0))

typedef struct {
  int top;
  int left;
  int height;
  int width;
} frame;

extern u16 *videoBuffer;
/*
 * Sets the pixel at (r,c) to the specified color
 */
void set_pixel(int r, int c, u16 color);

/*
 * Fill the given frame with the given color
 *
 */
void fill_frame(frame bounds, u16 color);

void delay(int n);
