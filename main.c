#include "screen.h"

int main()
{
  REG_DISPCNT = MODE; 
  frame rect = {0, SCREEN_WIDTH - 20, 20, 20};
  fill_frame(rect, WHITE);
  while(1)
  {
    wait_for_vblank();
    translate_horiz(&rect, -1);
  }
  return 1;
}
