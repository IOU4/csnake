#include <stdlib.h>
#include <stdbool.h>

typedef struct NK {
   int y_loc;
   int x_loc;
   struct NK *next;
}Body;


Body* create_Body(int y, int x) {
   Body *tmp = malloc(sizeof(Body));
   tmp->next = NULL;
   tmp->y_loc = y;
   tmp->x_loc = x;
   return tmp;
}

void delete_last(Body *head) {
   Body *tmp = head;
   while(tmp->next != NULL && tmp->next->next != NULL)
      tmp = tmp->next;
   free(tmp->next);
   tmp->next = NULL;
}

void add_head(int new_y, int new_x, Body *head, bool del_last) {
   Body *tmp = create_Body(head->y_loc, head->x_loc);
   tmp->next = head->next;
   head->next = tmp;
   head->y_loc = new_y;
   head->x_loc = new_x;
   if(del_last) 
      delete_last(head);
}

void add_end(Body *head, Body *node) {
   Body *tmp = head;
   while(tmp->next != NULL)
      tmp = tmp->next;
   tmp->next = node;
}

Body* find_last(Body* head) {
   Body *tmp = head;
   while(tmp->next != NULL)
      tmp = tmp->next;
   return tmp;
}
