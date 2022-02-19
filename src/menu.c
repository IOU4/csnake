#include <ncurses.h>
#include <stdio.h>
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

void print_score(WINDOW *menu, int score, int high_score) {
  mvwprintw(menu, 1, 1, "score = %d ", score);
  mvwprintw(menu, 2, 1, "high_score = %d ", high_score);
  wrefresh(menu);
}

void store_high_score(int high_score) {
  FILE *file =  fopen("high_score.bin", "wb");
  int score[1] = {high_score};
  fwrite(score, sizeof *score, 1, file);
  if(ferror(file)) perror("error reading high_score.bin");
  fclose(file);
}

int get_high_score() {
  FILE *file =  fopen("high_score.bin", "rb");
  int score[1] = {0};
  int ret = fread(score, sizeof(*score), 1, file);
  if(ret == 1) return score[0];
  if(ferror(file)) perror("error reading high_score.bin");
  fclose(file);
  return -1;
}
