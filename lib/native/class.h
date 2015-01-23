#ifndef FxN_Class_h
#define FxN_Class_h 1

#include "../bricks/string.h"

typedef struct FxN_Class {
  FxB_String  *name;
  struct FxN_Class *ancestor;
} FxN_Class;

#define fxn_class_name(C)       ((C)->name)
#define fxn_class_ancestor(C)   ((C)->ancestor)
#define fxn_class_free(C)       (fx_pfree(C)) // TODO: more better

#endif
