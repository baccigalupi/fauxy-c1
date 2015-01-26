#ifndef FxN_Object_h
#define FxN_Object_h 1

#include "../bricks/hash_map.h"
#include "class.h"
#include "pool.h"

typedef struct FxN_Object {
  FxN_Class     *scope;
  FxB_HashMap   *attributes;
  FxI_Pool      *pool;
} FxN_Object;

#define FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE   50
#define FXN_VALUE_KEY                       "__value__"

#define fxn_object_scope(O)                 ((O)->scope)

#define fxn_object_pool(O)                  ((O)->pool)

#define fxn_object_attributes(O)            ((O)->attributes)
#define fxn_object_get_attribute(O, K)      (fxb_hash_map_get(fxn_object_attributes(O), K))
#define fxn_object_set_attribute(O, K, V)   (fxb_hash_map_set(fxn_object_attributes(O), K, V))

#define fxn_object_free(O)                  (fxn_class_free(fxn_object_scope(O)), fxb_hash_map_free(fxn_object_attributes(O)), fx_pfree(O))

FxN_Object *FxN_Object_create(FxI_Pool *pool, FxN_Class *scope);

#endif