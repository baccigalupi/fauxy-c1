#ifndef FxN_MethodGroup_h
#define FxN_MethodGroup_h 1

#include "../bricks/helpers.h"
#include "../bricks/list.h"

typedef struct FxN_MethodGroup {
  char             *name;
  FxB_List         *functions;
} FxN_MethodGroup;

#define fxn_method_group_name(C)        ((C)->name)
#define fxn_method_group_functions(C)   ((C)->functions)
#define fxn_method_group_free(C)        (fx_pfree(C)) // TODO: more better

#endif
