#ifndef __FxB_FxB_List_h
#define __FxB_FxB_List_h 1

#include "node.h"

typedef struct FxB_List {
  int length;
  struct FxB_Node *first;
  struct FxB_Node *last;
} FxB_List;

#define fxb_list_length(L)        ((L)->length)
#define fxb_list_node_first(L)    ((L)->first)
#define fxb_list_first(L)         ((L)->first ? (L)->first->value : NULL)
#define fxb_list_node_last(L)     ((L)->last)
#define fxb_list_last(L)          ((L)->last == NULL  ? NULL : (L)->last->value)
#define fxb_list_each(L, N)       for (N = L->first; N != NULL; N = N->next)

FxB_List *FxB_List_create();

FxB_Node *fxb_list_pop_node(FxB_List *list);
void      fxb_list_push_node(FxB_List *list, FxB_Node *node);
FxB_Node *fxb_list_shift_node(FxB_List *list);
void      fxb_list_unshift_node(FxB_List *list, FxB_Node *node);

void  fxb_list_push(   FxB_List *list, void *value);
void *fxb_list_pop(    FxB_List *list);
void  fxb_list_unshift(FxB_List *list, void *value);
void *fxb_list_shift(  FxB_List *list);

void  fxb_list_free(FxB_List *list);
void  fxb_list_r_free(FxB_List *list);


#endif
