#ifndef FxN_Class_h
#define FxN_Class_h 1

// Class is an object too. I decided that while I was asleep, after wondering about
// it for a couple days.

#include "structs.h"
#include "function.h"
#include "object.h"

//#define fxn_class_name(C)          (char *)(fxn_object_value(C)) // must change value to a void *
#define fxn_class_super_class(C)   (fxn_object_scope(C))

#define fxn_class_method_count(C)           (fxb_hash_map_length(fxn_object_attributes(C)))
#define fxn_class_get_method_group(C, K)    (fxb_hash_map_get(fxn_object_attributes(C), K))
#define fxn_class_set_method_group(C, K, V) (fxb_hash_map_set(fxn_object_attributes(C), K, V))

#define fxn_class_free(C)          (fx_pfree(C)) // TODO: more better

void          fxn_class_set_method(FxN_Object *self, char *method_name, FxN_Function *function);
FxN_Function *fxn_class_get_method(FxN_Object *self, char *method_name);

#endif
