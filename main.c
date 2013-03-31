#include "screen.h"
#include "utils.h"
#include "buttons.h"
#include "pacman.h"
#include "pacman_pebble.h"

void update_velocities(Velocity *velocity, button_data buttons);
void draw_user_velocities(Frame *frame, Velocity *velocity);

int main()
{
  REG_DISPCNT = MODE;
  PacmanPebble pebbles[] = {
    {
      &((Frame){30, 50, 10, 10}),
      0
    }
  };
  int num_pacman_pebbles = LENGTH(pebbles);
  Pacman shots[] = {
    {
      &((Frame) { 20, 50, 40, 40 }),
      &((Velocity) {0, 0})
    }
  };
  int cur_shot = 0;
  int total_shots = LENGTH(shots);
  Frame velocity_frame = {0, SCREEN_HEIGHT - 40, 40, 40};
  int bg_color = BLACK;

  while(1)
  {
    while(cur_shot < total_shots)
    {
      Pacman *cur_pac_shot = (shots + cur_shot);
      draw_pacman(cur_pac_shot);
      draw_pebbles(pebbles, num_pacman_pebbles);
 
      Velocity velocities = {0,0};
      int buttons = BUTTONS_MASK;
      while(!KEY_PRESSED(buttons))
      {
        update_velocities(&velocities, buttons);
        draw_user_velocities(&velocity_frame, &velocities);
      }

      erase_frame(&velocity_frame, bg_color);

      //now we run simulation
    /*  while(!off_screen(cur_shot))
      {
        for (i = 0; i < num_pacman_pebbles; i++) {
          pacman_pebble *cur_pebble = (pebbles + i);
          if(!cur_pebble->is_hit)
          {
            check_collision(cur_pac_shot, cur_pebble);
          }
        }
        move_shot(cur_pac_shot);
        draw_pacman(cur_pac_shot);
        draw_pebbles(pebbles, num_pacman_pebbles);
 
     } */

      cur_shot++;
    }
  }

  return 1;
}

void update_velocities(Velocity *velocity, button_data buttons)
{

}

void draw_user_velocities(Frame *frame, Velocity *velocity)
{

}
