#include "game.h"

int run_game(GameData *data)
{
  int cur_shot = 0;
  while(cur_shot < data->num_shots)
  {
    Pacman *cur_pac_shot = (data->shots + cur_shot);
    draw_pacman(cur_pac_shot);
    draw_pebbles(data->pebbles, data->num_pebbles);
    *cur_pac_shot->velocity = *(data->old_velocity);
    Velocity *velocity = cur_pac_shot->velocity;
    while(!KEY_PRESSED(START))
    {
      update_velocities(velocity);
      wait_for_vblank();
      draw_user_velocities(data->velocity_frame_x, data->velocity_frame_y, velocity);
      draw_pacman(cur_pac_shot);
    }
    *(data->old_velocity ) = *cur_pac_shot->velocity;//MUST save old shot

    erase_frame(data->velocity_frame_x, data->bg_color);
    erase_frame(data->velocity_frame_y, data->bg_color);

    //now we run simulation
    fill_frame(data->indicator, GREEN);
    int i = 0;
    while(!off_screen(cur_pac_shot->frame))
    {
      for (i = 0; i < data->num_pebbles; i++) {
        PacmanPebble *cur_pebble = (data->pebbles + i);
        check_collision(cur_pac_shot, cur_pebble);
      }
      wait_for_vblank();
      erase_frame(cur_pac_shot->frame, data->bg_color);
      move_shot(cur_pac_shot);
      draw_pebbles(data->pebbles, data->num_pebbles);
      draw_pacman(cur_pac_shot);
   }

    erase_frame(cur_pac_shot->frame, data->bg_color);
    cur_shot++;
  }
  fill_frame(data->indicator, RED);
  return 0;
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

  vx_frame->width = MAX(velocity->vx, 2);
  vy_frame->top = 75 + (velocity->vy < 0 ? 0 : -velocity->vy);
  vy_frame->height = ABS(velocity->vy);

  fill_frame(vx_frame, WHITE);
  fill_frame(vy_frame, WHITE);
}
