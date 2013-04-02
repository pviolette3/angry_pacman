#ifndef __GAME_H__
#define __GAME_H__

#include "screen.h"
#include "buttons.h"
#include "pacman_pebble.h"
#include "pacman.h"
#include "utils.h"

typedef struct{
  PacmanPebble *pebbles;//array !!
  int num_pebbles;
  Pacman *shots; // array !!
  int num_shots;
  Frame *velocity_frame_x;
  Frame *velocity_frame_y;
  u16 bg_color;
  Frame *indicator;
  Velocity *old_velocity;
} GameData;

int run_game(GameData *game); 
void update_velocities(Velocity *velocity);
void draw_user_velocities(Frame *vx_frame, Frame *vy_frame, Velocity *velocity);
#endif
