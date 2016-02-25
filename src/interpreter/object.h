#ifndef FxI_Object_h
#define FxI_Object_h 1

#include "../bricks/_bricks.h"
#include "../parser/_parser.h"

#include "structs.h"

#define FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE   50

#define fxi_object_class(O)                 ((O)->klass)
#define fxi_object_attributes(O)            ((O)->attributes)
#define fxi_object__value(O)                ((O)->value)

#define fxi_object_value(O)                 (FxP_Expression *)((O)->value)

#define fxi_object_get_attribute(O, K)      (fxb_hash_map_get(fxi_object_attributes(O), K))
#define fxi_object_set_attribute(O, K, V)   (fxb_hash_map_set(fxi_object_attributes(O), K, V))
#define fxi_object_attributes_length(O)     (fxb_hash_map_length(fxi_object_attributes(O)))

#define fxi_object_free(O)                  (fxb_hash_map_free(fxi_object_attributes(O)), fx_pfree(O))

FxI_Object *FxI_Object_create(FxI_Interpreter *interpreter, FxI_Object *klass);
FxI_Object *fxi_object_set(FxI_Object *self, char *key, FxI_Object *value);

#endif
