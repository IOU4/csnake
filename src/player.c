#include "mouvment.h"
#include <ncurses.h>

typedef struct {
   WINDOW *win;
   int head_char;
   int body_char;
   int y_max;
   int x_max;
   Body *head;
}Snake;


Snake init_snake(WINDOW *win, int head_char, int body_char, int y_max, int x_max, Body *head) {
   Snake tmp;
   tmp.win = win;
   tmp.head_char = head_char;
   tmp.body_char = body_char;
   tmp.y_max = y_max;
   tmp.x_max = x_max;
   tmp.head = head;
   return tmp;
}

int m_up(int y, int height) {
   y = (y == 1) ? height-2 : y-1;
   return y;
}

int m_down(int y, int height) {
   y = y == height-2 ? 1 : y+1;
   return y;
}

int m_left(int x, int width) {
   x = x <= 1 ? width-2 : x-1;
   return x;
}

int m_right(int x, int width) {
   x = x >= width-2 ? 1 : x+1;
   return x;
}

void display_snake(WINDOW *win, Body *head, int head_char, int body_char) {
   Body *tmp = head->next;
   mvwaddch(win, head->y_loc, head->x_loc, head_char);
   while(tmp != NULL) {
      mvwaddch(win, tmp->y_loc, tmp->x_loc, body_char);
      tmp = tmp->next;
   }
   wrefresh(win);
}

void make_move(Snake snake) {
   WINDOW *win = snake.win; Body *head = snake.head; int height = snake.y_max; int width = snake.x_max; int head_char = snake.head_char; int body_char = snake.body_char;
   wtimeout(win, 200);
   int direction;
   bool delete = true;
   while(1) {
      display_snake(win, head, head_char, body_char);
      int c = wgetch(win);
      if(c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT)
         direction = c;
      Body *last = find_last(head);
      mvwaddch(win, last->y_loc, last->x_loc, ' ');
      switch(direction) {
         case KEY_UP:
            add_head(m_up(head->y_loc, height), head->x_loc, head, delete);
            break;
         case KEY_DOWN: 
            add_head(m_down(head->y_loc, height), head->x_loc, head, delete);
            break;
         case KEY_LEFT: 
            add_head(head->y_loc, m_left(head->x_loc, width), head, delete);
            break;
         case KEY_RIGHT:
            add_head(head->y_loc, m_right(head->x_loc, width), head, delete);
            break;
      }
      delete = true;
      if (c == 'q') break;
      if (c == 'a') delete = false;
   }
}
