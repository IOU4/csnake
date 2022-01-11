#include "src/player.h"
#include <locale.h>
#include <ncurses.h>

#define height 20
#define width 30

int main() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();

  WINDOW *playground = newwin(height, width, 0, 0);
  refresh();
  box(playground, 0, 0);
  wrefresh(playground);
  keypad(playground, true);
  curs_set(0);

  Body *head = create_Body(10, 15);

  Snake snake = init_snake(playground, "ﱢ", "ﱢ", height, width, head);
  make_move(snake);

  getch();
  endwin();
  return 0;
}
