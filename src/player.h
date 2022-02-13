#ifndef PLAYER_H
#define PLAYER_H

#include "menu.h"
#include "egg.h"
#include <ncurses.h>
#include <string.h>

typedef struct {
  WINDOW *win;
  char *head_char;
  char *body_char;
  int y_max;
  int x_max;
  Body *head;
} Snake;

Snake init_snake(WINDOW *win, char *head_char, char *body_char, int y_max, int x_max, Body *head);
int m_up(int y, int height);
int m_down(int y, int height);
int m_left(int x, int width);
int m_right(int x, int width);
void display_snake(Snake snake);
void get_direction(int c, int *direction);
void redirect(int direction, Body *head, int height, int width, bool delete_last);
bool is_head_on_body(Body *head);
void make_move(Snake snake, WINDOW* menu);
void play(int width, int height, float percentage, WINDOW *menu);

#include "player.c"

#endif
