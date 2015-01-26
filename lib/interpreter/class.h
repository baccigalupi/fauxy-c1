#ifndef FxN_Class_h
#define FxN_Class_h 1

#include "../bricks/helpers.h"
#include "../bricks/hash_map.h"

typedef struct FxN_Class {
  char             *name;
  struct FxN_Class *super_class;
  FxB_HashMap      *method_groups;
} FxN_Class;

#include "function.h"

#define fxn_class_name(C)          ((C)->name)
#define fxn_class_super_class(C)   ((C)->super_class)
#define fxn_class_free(C)          (fx_pfree(C)) // TODO: more better
#define fxn_class_method_groups(C) ((C)->method_groups)

FxN_Class    *FxN_Class_create(char *name, FxN_Class *super_class);
void          fxn_class_set_method(FxN_Class *self, char *method_name, FxN_Function *function);
FxN_Function *fxn_class_get_method(FxN_Class *self, char *method_name);

#endif
