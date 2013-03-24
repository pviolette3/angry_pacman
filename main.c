#include "screen.h"

int main()
{
  REG_DISPCNT = MODE; 
  frame rect = {0,0, 20, 60};
  fill_frame(rect, WHITE);
  while(1)
  {
    wait_for_vblank();
    translate_vert(&rect, 1);
  }
  return 1;
}
