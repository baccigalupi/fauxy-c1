#ifndef FxI_Object_h
#define FxI_Object_h 1

#include "../bricks/_bricks.h"
#include "../parser/_parser.h"

#include "structs.h"

#define FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE   50

#define fxn_object_type(O)                  ((O)->type)
#define fxn_object_scope(O)                 ((O)->scope)
#define fxn_object_interpreter(O)           ((O)->interpreter)
#define fxn_object_attributes(O)            ((O)->attributes)
#define fxn_object__value(O)                ((O)->value)

#define fxn_object_closed(O)                ((O)->closed)
#define fxn_object_is_closed(O)             fxn_object_closed(O)
#define fxn_object_is_open(O)               (!fxn_object_closed(O))
#define fxn_object_close(O)                 (fxn_object_closed(O) = true)
#define fxn_object_open(O)                  (fxn_object_closed(O) = false)

#define fxn_object_value(O)                 (FxP_Expression *)((O)->value)

#define fxn_object_get_attribute(O, K)      (fxb_hash_map_get(fxn_object_attributes(O), K))
#define fxn_object_set_attribute(O, K, V)   (fxb_hash_map_set(fxn_object_attributes(O), K, V))
#define fxn_object_attributes_length(O)     (fxb_hash_map_length(fxn_object_attributes(O)))

#define fxn_object_free(O)                  (fxb_hash_map_free(fxn_object_attributes(O)), fx_pfree(O))

FxI_Object *FxI_Object_create(FxI_Interpreter *interpreter, FxI_Object *scope);
FxI_Object *fxn_object_set(FxI_Object *self, char *key, FxI_Object *value);

#endif
