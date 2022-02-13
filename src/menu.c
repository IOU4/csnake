#include <ncurses.h>
WINDOW * prompt_menu(int width, int height, float percentage) {
  const int startx_menu = width-width*percentage;
  const int menu_width = width*percentage;

  WINDOW *menu = newwin(height, menu_width, 0, startx_menu);
  box(menu, 0, 0);
  refresh();
  wrefresh(menu);
  keypad(menu, true);
  return menu;
}

void print_score(WINDOW *menu, int score ) {
  mvwprintw(menu, 1, 1, "score = %d ", score);
  wrefresh(menu);
}
