#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

WINDOW * prompt_menu(int width, int height, float percentage);
void print_score(WINDOW *menu, int score, int heigh_score);
#include "menu.c"
#endif
