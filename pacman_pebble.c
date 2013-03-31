#include "pacman_pebble.h"
#include "screen.h"

void draw_pebbles(PacmanPebble arr[], int length)
{
  for (int i = 0; i < length; i++) {
    PacmanPebble * cur = arr + i;
     if (!cur->is_hit) {
       fill_frame(cur->frame, WHITE);
     }
  }
}
