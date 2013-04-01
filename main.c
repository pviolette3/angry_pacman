#include "screen.h"
#include "utils.h"
#include "buttons.h"
#include "pacman.h"
#include "pacman_pebble.h"

void update_velocities(Velocity *velocity);
void draw_user_velocities(Frame *vx_frame, Frame *vy_frame, Velocity *velocity);

int main()
{
  REG_DISPCNT = MODE3 | VIDEO_MODE;
  PacmanPebble pebbles[] = {
    {
      &((Frame){50, 160, 10, 10}),
      0
    },
   {
      &((Frame){60, 80, 10, 10}),
      0
    }
  };
  int num_pacman_pebbles = LENGTH(pebbles);
  Pacman shots[] = {
    {
      &((Frame) { 70, 50, 10, 10 }),
      &((Velocity) {0, 0})
    },
    {
      &((Frame) { 70, 50, 10, 10 }),
      &((Velocity) {0, 0})
    },
    {
      &((Frame) { 70, 50, 10, 10 }),
      &((Velocity) {0, 0})
    }
  };
  int cur_shot = 0;
  int total_shots = LENGTH(shots);
  Frame velocity_frame_x = {75, 55, 0, 0};
  Frame velocity_frame_y = { 75, 55, 0, 0};
  Frame indicator = {0,0,15,15};
  int bg_color = BLACK;

  while(1)
  {
    while(cur_shot < total_shots)
    {
      Pacman *cur_pac_shot = (shots + cur_shot);
      draw_pacman(cur_pac_shot);
      draw_pebbles(pebbles, num_pacman_pebbles);
      Velocity *velocity = cur_pac_shot->velocity;
      while(!KEY_PRESSED(START))
      {
        update_velocities(velocity);
        wait_for_vblank();
        draw_user_velocities(&velocity_frame_x, &velocity_frame_y, velocity);
        draw_pacman(cur_pac_shot);
      }

      erase_frame(&velocity_frame_x, bg_color);
      erase_frame(&velocity_frame_y, bg_color);

      //now we run simulation
      fill_frame(&indicator, GREEN);
      int i = 0;
      while(!off_screen(cur_pac_shot->frame))
      {
        for (i = 0; i < num_pacman_pebbles; i++) {
          PacmanPebble *cur_pebble = (pebbles + i);
          check_collision(cur_pac_shot, cur_pebble);
        }
        wait_for_vblank();
        erase_frame(cur_pac_shot->frame, bg_color);
        move_shot(cur_pac_shot);
        draw_pebbles(pebbles, num_pacman_pebbles);
        draw_pacman(cur_pac_shot);
     }

      erase_frame(cur_pac_shot->frame, bg_color);
      cur_shot++;
    }
    fill_frame( &indicator, RED);
  }

  return 1;
}

void update_velocities(Velocity *velocity)
{
  if(KEY_PRESSED(D_LEFT))
  {
    velocity->vx = MAX(velocity->vx - 2, 0);
  }
  if(KEY_PRESSED(D_RIGHT))
  {
    velocity->vx = MIN(velocity->vx + 2, SCREEN_WIDTH / 4);
  }

  if(KEY_PRESSED(D_DOWN))
  {
    velocity->vy = MAX(velocity->vy - 2, -SCREEN_HEIGHT / 3);
  }

  if(KEY_PRESSED(D_UP))
  {
    velocity->vy = MIN(velocity->vy + 2, SCREEN_HEIGHT / 3);
  }
}

void draw_user_velocities(Frame *vx_frame, Frame *vy_frame, Velocity *velocity)
{
  fill_frame(vx_frame, BLACK);
  fill_frame(vy_frame, BLACK);

  vx_frame->width = velocity->vx;
  vy_frame->top = 75 + (velocity->vy < 0 ? 0 : -velocity->vy);
  vy_frame->height = ABS(velocity->vy);

  fill_frame(vx_frame, WHITE);
  fill_frame(vy_frame, WHITE);
}
