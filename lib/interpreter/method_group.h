#ifndef FxN_MethodGroup_h
#define FxN_MethodGroup_h 1

#include "../bricks/_bricks.h"

typedef struct FxN_MethodGroup {
  char             *name;
  FxB_List         *functions;
} FxN_MethodGroup;

#define fxn_method_group_name(C)        ((C)->name)
#define fxn_method_group_functions(C)   ((C)->functions)
#define fxn_method_group_free(C)        (fx_pfree(C)) // TODO: more better

#define fxn_method_group_push(C, V)     (fxb_list_push(fxn_method_group_functions(C), V))
#define fxn_method_group_length(C)      (fxb_list_length(fxn_method_group_functions(C)))

FxN_MethodGroup *FxN_MethodGroup_create(char *method_name);

#endif
