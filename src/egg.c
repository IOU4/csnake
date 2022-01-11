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

int *get_random_egg(int height, int width) {
  srand(time(0));
  int *rands = malloc(2 * sizeof(int));
  *rands = (rand() % (height - 2)) + 1;
  *(rands + 1) = (rand() % (width - 2)) + 1;
  return rands;
}

bool is_egg_on_snake(Body *head, int *randoms) {
  Body *tmp = head;
  while (tmp->next != NULL) {
    if (tmp->y_loc == randoms[0] && tmp->x_loc == randoms[1])
      return true;
    tmp = tmp->next;
  }
  return false;
}

void display_egg(Body *head, WINDOW *win, int height, int width, Egg *egg) {
  if (egg->no_eggs) {
    int *rands = get_random_egg(height, width);
    while (is_egg_on_snake(head, rands))
      rands = get_random_egg(height, width);
    egg->y_loc = *rands;
    egg->x_loc = *(rands + 1);
    mvwprintw(win, egg->y_loc, egg->x_loc, "");
    egg->no_eggs = false;
  }
  wrefresh(win);
}

void update_egg_position(Egg *egg, int y, int x) {
  egg->y_loc = y;
  egg->x_loc = x;
}
