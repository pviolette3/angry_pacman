#ifndef __PACMAN_H__
#define __PACMAN_H__

#include "screen.h"
#include "pacman_pebble.h"

typedef struct
{
  int vx;
  int vy;
} Velocity;

typedef struct
{
  Frame *frame;
  Velocity *velocity;
} Pacman;

void check_collision(Pacman *pacman, PacmanPebble *pebble);
void move_shot(Pacman *pacman);
void draw_pacman(Pacman *pacman);
#endif
