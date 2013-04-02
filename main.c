#include "game.h"
#include "static_screens.h"

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
GameData games[] = {
  //level 0
  {
    pebbles,
    LENGTH(pebbles),
    shots,
    LENGTH(shots),
    &((Frame){75, 55, 1, 1}),//velocity frame x
    &((Frame) { 75, 55, 1, 1}), //velocity frame y
    BLACK, //background
    &((Frame) {0,0,15,15}),
    &((Velocity) {0,0})
  }
//level 1

};
int num_levels = LENGTH(games);

int main()
{
  REG_DISPCNT = MODE3 | VIDEO_MODE;
 
  while(1)
  {
    show_splash();
    int cur_level = 0;
    for(cur_level = 0; cur_level < num_levels; )
    { 
      if(run_game(games + cur_level))
      {
        cur_level++;
        show_level_passed();
      }else {
        show_level_retry();
      }
    }
    show_game_ended();
  }

  return 1;
}

