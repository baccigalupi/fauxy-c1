#ifndef __bricks_list_h
#define __bricks_list_h

#include "node.h"

typedef struct List {
  int length;
  struct Node *first;
  struct Node *last;
} List;

#define list_length(L)        ((L)->length)
#define list_node_first(L)    ((L)->first)
#define list_first(L)         ((L)->first ? (L)->first->value : NULL)
#define list_node_last(L)     ((L)->last)
#define list_last(L)          ((L)->last == NULL  ? NULL : (L)->last->value)
#define list_each(L, N)       for (N = L->first; N != NULL; N = N->next)

List *List_create();

Node *list_pop_node(List *list);
void  list_push_node(List *list, Node *node);
Node *list_shift_node(List *list);
void  list_unshift_node(List *list, Node *node);

void  list_push(   List *list, void *value);
void *list_pop(    List *list);
void  list_unshift(List *list, void *value);
void *list_shift(  List *list);

void  list_free(List *list);
void  list_r_free(List *list);


#endif
