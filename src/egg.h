#ifndef EGG_H
#define EGG_H

#include "mouvment.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int y_loc;
  int x_loc;
  int counter;
  bool no_eggs;
} Egg;

int * get_random_egg(int height, int width);
bool is_egg_on_snake(Body *head, int *randoms);
void display_egg(Body *head, WINDOW *win, int height, int width, Egg *egg);
void update_egg_position(Egg *egg, int y, int x);
#include "egg.c"

#endif

