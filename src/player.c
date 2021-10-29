#include "mouvment.h"
#include "egg.h"
#include <ncurses.h>
#include <unistd.h>

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

void display_snake(Snake snake) {
   // print head
   Body *tmp = snake.head->next;
   mvwaddch(snake.win, snake.head->y_loc, snake.head->x_loc, snake.head_char);

   // print body
   while(tmp != NULL) {
      mvwaddch(snake.win, tmp->y_loc, tmp->x_loc, snake.body_char);
      tmp = tmp->next;
   }

   wrefresh(snake.win);
}

void get_direction (int c, int *direction) {
   if(
      c == 'k' 
      || c == 'j'
      || c == 'h'
      || c == 'l'
      || c == KEY_UP 
      || c == KEY_DOWN 
      || c == KEY_LEFT 
      || c == KEY_RIGHT
      )
      if(!(
         (c == KEY_UP && *direction == KEY_DOWN) 
         || (c == KEY_DOWN && *direction == KEY_UP) 
         || (c == KEY_LEFT && *direction == KEY_RIGHT) 
         || (*direction == KEY_LEFT && c == KEY_RIGHT)
         ))
         *direction = c;
}

void redirect(int direction, Body *head, int height, int width, bool delete) {
      switch(direction) {
         case KEY_UP:
         case 'k':
            add_head(m_up(head->y_loc, height), head->x_loc, head, delete);
            break;
         case KEY_DOWN: 
         case 'j':
            add_head(m_down(head->y_loc, height), head->x_loc, head, delete);
            break;
         case KEY_LEFT: 
         case 'h':
            add_head(head->y_loc, m_left(head->x_loc, width), head, delete);
            break;
         case KEY_RIGHT:
         case 'l':
            add_head(head->y_loc, m_right(head->x_loc, width), head, delete);
            break;
      }
}

bool is_head_on_body(Body *head) {
   Body *tmp = head->next;
   while(tmp != NULL) {
      if(head->x_loc == tmp->x_loc && head->y_loc == tmp->y_loc) 
         return true;
      tmp = tmp->next;
   }
   return false;
}

void make_move(Snake snake) {
   WINDOW *win = snake.win; Body *head = snake.head; int height = snake.y_max; int width = snake.x_max; int head_char = snake.head_char; int body_char = snake.body_char;
   wtimeout(snake.win, 200);

   int direction;
   bool delete = true;

   Egg *egg = malloc(sizeof(Egg));
   egg->no_eggs = true;
   
   while(1) {
      display_snake(snake);
      display_egg(win, snake.y_max, snake.x_max, egg);

      int c = wgetch(win);
      //usleep(200000);
      get_direction(c, &direction);

      // delete last node
      Body *last = find_last(head);
      mvwaddch(win, last->y_loc, last->x_loc, ' ');

      redirect(direction, head, height, width, delete);

      delete = true;
      if (c == 'q') break;
      if (is_head_on_body(head)) break;
      if(c == 'v' ) mvwprintw(win, 17, 2, "egg_y = %d, head_y = %d \n egg_x = %d, head_x = %d \n no_eggs = %d", egg->y_loc, head->y_loc, egg->x_loc, head->x_loc, egg->no_eggs);
      if (egg->y_loc == head->y_loc && egg->x_loc == head->x_loc || c == 'a'){
         delete = false;
         egg->no_eggs = true;
      }
   }
}
