#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int y_loc;
   int x_loc;
   int counter;
   bool no_eggs;
}Egg;

int * get_random_egg (int height, int width) {
   srand(time(0));
   int *rands = malloc(2*sizeof(int)) ; 
   *rands = (rand()%(height-2))+1;
   *(rands+1) = (rand()%(width-2))+1;
   return rands;
}

void display_egg(WINDOW *win, int height, int width, Egg *egg) {
   if(egg->no_eggs) {
      int *rands = get_random_egg (height, width);
      egg->y_loc = *rands;
      egg->x_loc = *(rands+1);
      mvwaddch(win, egg->y_loc, egg->x_loc, 'o');
      egg->no_eggs = false;
   }
   wrefresh(win);
}

void update_egg_pos(Egg *egg, int y, int x) {
   egg->y_loc = y;
   egg->x_loc = x;
}
