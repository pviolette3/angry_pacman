#ifndef __PACMAN_PEBBLE_H__
#define __PACMAN_PEBBLE_H__
#include "screen.h"
typedef struct {
  Frame *frame;
  int is_hit;
} PacmanPebble;

void draw_pebbles(PacmanPebble arr[], int length);
#endif
