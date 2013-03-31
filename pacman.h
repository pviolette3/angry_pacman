#ifndef __PACMAN_H__
#define __PACMAN_H__
#include "screen.h"
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

void draw_pacman(Pacman *pacman);
#endif
