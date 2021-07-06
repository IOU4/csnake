#include <ncurses.h>
#include "src/player.h"

#define height 20
#define width 30

int main() {
   
   initscr();
   noecho();
   
   WINDOW *win = newwin(height, width, 0, 0);
   refresh();
   box(win, 0, 0);
   wrefresh(win);
   keypad(win, true);
   curs_set(0);

   Body *head = create_Body(10, 15);

   Snake snake = init_snake(win, '@', '-', height, width, head);
   make_move(snake);
   
   getch();
   endwin();
   return 0;
}
