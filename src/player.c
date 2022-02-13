#include "player.h"
Snake init_snake(WINDOW *win, char *head_char, char *body_char, int y_max, int x_max, Body *head) {
  Snake tmp;
  tmp.head_char = malloc(4);
  tmp.body_char = malloc(4);
  tmp.win = win;
  strcpy(tmp.head_char, head_char);
  strcpy(tmp.body_char, body_char);
  tmp.y_max = y_max;
  tmp.x_max = x_max;
  tmp.head = head;
  return tmp;
}

int m_up(int y, int height) {
  y = (y == 1) ? height - 2 : y - 1;
  return y;
}

int m_down(int y, int height) {
  y = y == height - 2 ? 1 : y + 1;
  return y;
}

int m_left(int x, int width) {
  x = x <= 1 ? width - 2 : x - 1;
  return x;
}

int m_right(int x, int width) {
  x = x >= width - 2 ? 1 : x + 1;
  return x;
}

void display_snake(Snake snake) {
  // print head
  Body *tmp = snake.head->next;
  mvwprintw(snake.win, snake.head->y_loc, snake.head->x_loc, "%s",
            snake.head_char);
  // print body
  while (tmp != NULL) {
    mvwprintw(snake.win, tmp->y_loc, tmp->x_loc, "%s", snake.body_char);
    tmp = tmp->next;
  }
  wrefresh(snake.win);
}

void get_direction(int c, int *direction) {
  if (c == 'k' || c == 'j' || c == 'h' || c == 'l' || c == KEY_UP ||
      c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT)
    if (!(((c == KEY_UP || c == 'k') &&
           (*direction == KEY_DOWN || *direction == 'j')) ||
          ((c == KEY_DOWN || c == 'j') &&
           (*direction == KEY_UP || *direction == 'k')) ||
          ((c == KEY_LEFT || c == 'h') &&
           (*direction == KEY_RIGHT || *direction == 'l')) ||
          (c == KEY_RIGHT || c == 'l') &&
              ((*direction == KEY_LEFT || *direction == 'h'))))
      *direction = c;
}

void redirect(int direction, Body *head, int height, int width,  bool delete_last) {
  switch (direction) {
  case KEY_UP:
  case 'k':
    add_head(m_up(head->y_loc, height), head->x_loc, head, delete_last);
    break;
  case KEY_DOWN:
  case 'j':
    add_head(m_down(head->y_loc, height), head->x_loc, head, delete_last);
    break;
  case KEY_LEFT:
  case 'h':
    add_head(head->y_loc, m_left(head->x_loc, width), head, delete_last);
    break;
  case KEY_RIGHT:
  case 'l':
    add_head(head->y_loc, m_right(head->x_loc, width), head, delete_last);
    break;
  }
}

bool is_head_on_body(Body *head) {
  Body *tmp = head->next;
  while (tmp != NULL) {
    if (head->x_loc == tmp->x_loc && head->y_loc == tmp->y_loc)
      return true;
    tmp = tmp->next;
  }
  return false;
}

void make_move(Snake snake, WINDOW *menu) {
  WINDOW *win = snake.win;
  Body *head = snake.head;
  int height = snake.y_max;
  int width = snake.x_max;
  int score = 0;
  wtimeout(snake.win, 200);

  int direction;
  bool delete_last = true;

  Egg *egg = malloc(sizeof(Egg));
  egg->no_eggs = true;

  while (1) {
    display_snake(snake);
    print_score(menu, score);
    display_egg(snake.head, win, snake.y_max, snake.x_max, egg);

    int c = wgetch(win);
    get_direction(c, &direction);

    // delete_last last node
    Body *last = find_last(head);
    mvwaddch(win, last->y_loc, last->x_loc, ' ');

    redirect(direction, head, height, width, delete_last);

    delete_last = true;
    if (c == 'q' || is_head_on_body(head)){
      break;
    }
    if (c == 'v')
      mvwprintw(
          win, 17, 2,
          "egg_y = %d, head_y = %d \n egg_x = %d, head_x = %d \n no_eggs = %d",
          egg->y_loc, head->y_loc, egg->x_loc, head->x_loc, egg->no_eggs);
    if (c == 'a')
      delete_last = false;
    if (egg->y_loc == head->y_loc && egg->x_loc == head->x_loc) {
      egg->no_eggs = true;
      delete_last = false;
      score++;
    }
  }
}

void play(int width, int height, float percentage, WINDOW *menu) {
  int playground_width = width-width*percentage;
  WINDOW *playground = newwin(height, playground_width, 0, 0);
  box(playground, 0, 0);
  refresh();
  wrefresh(playground);
  keypad(playground, true);
  curs_set(0);
  Body *head = create_Body(height/2, width/2);
  Snake snake = init_snake(playground, "ﱢ", "ﱢ", height, playground_width, head);
  make_move(snake, menu);
}
