#ifndef MOUVMENT_H
#define MOUVMENT_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Body {
  int y_loc;
  int x_loc;
  struct Body *next;
} Body;

Body *create_Body(int y, int x);
void delete_last(Body *head);
void add_head(int new_y, int new_x, Body *head, bool del_last);
void add_end(Body *head, Body *node);
Body *find_last(Body *head);

#include "mouvment.c"

#endif
