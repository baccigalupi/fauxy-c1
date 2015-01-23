#ifndef FxN_Class_h
#define FxN_Class_h 1

#include "../bricks/list.h"
#include "../bricks/string.h"

typedef struct FxN_Class {
  FxB_String  *name;
  FxB_List    *ancestors;
} FxN_Class;

#define fxn_class_name(C)       ((C)->name)
#define fxn_class_ancestors(C)  ((C)->ancestors)
#define fxn_class_free(C)       (fx_pfree(C)) // TODO: more better

#endif
