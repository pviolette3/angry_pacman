#include "pacman.h"

void draw_pacman(Pacman *pacman)
{
  fill_frame(pacman->frame, YELLOW);
}

void check_collision(Pacman *pacman, PacmanPebble *pebble)
{
    Frame *pacman_frame = pacman->frame;
    Frame *pebble_frame = pebble->frame;
    if(intersect(pacman_frame, pebble_frame))
    {
    pebble->is_hit = 1;  
    }
}

static int shot_num = 0;
void move_shot(Pacman *pacman)
{
  if(! (shot_num++ % 2)) {
    pacman->velocity->vy = pacman->velocity->vy - 1;//gravity points down
  }
  pacman->frame->top = pacman->frame->top - pacman->velocity->vy / 10;//+ => going down
  pacman->frame->left = pacman->frame->left + pacman->velocity->vx / 10;
}
