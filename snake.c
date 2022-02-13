#include "src/menu.h"
#include "src/player.h"
#include <locale.h>
#include <ncurses.h>

#define height LINES
#define width COLS
#define percentage  0.20

int main() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  curs_set(0);
  WINDOW *menu = prompt_menu(width, height, percentage);
  play(width, height, percentage, menu);

  getch();
  endwin();
  return 0;
}
