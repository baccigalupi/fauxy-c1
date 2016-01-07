#ifndef FxI_Class_h
#define FxI_Class_h 1

// Class is an object too. I decided that while I was asleep, after wondering about
// it for a couple days.

#include "structs.h"
#include "function.h"
#include "object.h"

typedef FxI_Object FxI_Class;

#define fxn_class_name(C)          (char *)((C)->value)
#define fxn_class_super_class(C)   (fxn_object_scope(C))

#define fxn_class_method_count(C)           (fxb_hash_map_length(fxn_object_attributes(C)))
#define fxn_class_get_method_group(C, K)    (fxb_hash_map_get(fxn_object_attributes(C), K))
#define fxn_class_set_method_group(C, K, V) (fxb_hash_map_set(fxn_object_attributes(C), K, V))

#define fxn_class_free(C)          (fx_pfree(C)) // TODO: more better

FxI_Class              *FxI_Class_create(FxI_Interpreter *interpreter, char *name, FxI_Class *superclass);
void                    fxn_class_set_method(FxI_Class *self, char *method_name, FxI_FunctionDefinition *function);
FxI_FunctionDefinition *fxn_class_get_method(FxI_Class *self, char *method_name);

/*
 * Class methods:
 *    new
 *    extend, add, <<
 *    alias
 *    // `native` will be in the global space so any c function that returns a FxI_Object
 *    // can be made into a wrapped function
 *
 */

#endif
