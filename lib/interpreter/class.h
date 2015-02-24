#ifndef FxN_Class_h
#define FxN_Class_h 1

#include "../bricks/_bricks.h"

typedef struct FxN_Class {
  int              type;
  char             *name;
  struct FxN_Class *super_class;
  FxB_HashMap      *methods;
} FxN_Class;

#include "pool.h"
#include "function.h"

#define fxn_class_type(C)          ((C)->type)
#define fxn_class_name(C)          ((C)->name)
#define fxn_class_super_class(C)   ((C)->super_class)
#define fxn_class_methods(C)       ((C)->methods)

#define fxn_class_method_count(C)           (fxb_hash_map_length(fxn_class_methods(C)))
#define fxn_class_get_method_group(C, K)    (fxb_hash_map_get(fxn_class_methods(C), K))
#define fxn_class_set_method_group(C, K, V) (fxb_hash_map_set(fxn_class_methods(C), K, V))

#define fxn_class_free(C)          (fx_pfree(C)) // TODO: more better

FxN_Class    *FxN_Class_create(char *name, FxN_Class *super_class);

void          fxn_class_set_method(FxN_Class *self, char *method_name, FxN_Function *function);
FxN_Function *fxn_class_get_method(FxN_Class *self, char *method_name);

#endif
