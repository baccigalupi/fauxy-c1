#ifndef __FxB_HashMap_h
#define __FxB_HashMap_h

#include <string.h>
#include "node.h"
#include "array.h"

#include "helpers.h"

typedef struct FxB_HashMap {
  int length;
  int capacity;
  FxB_Array *values;
} FxB_HashMap;

#define fxb_hash_map_values(H)            ((H)->values)
#define fxb_hash_map_length(H)            ((H)->length)
#define fxb_hash_map_capacity(H)          ((H)->capacity)

#define fxb_hash_map_list_at_index(H, I)  (fxb_array_at_index(fxb_hash_map_values(H), I))
#define fxb_hash_map_index_for_key(H, K)  (fxb_string_hash(K) % fxb_hash_map_capacity(H))
#define fxb_hash_map_free(H)              ((fxb_hash_map_free_list_values(H)), (fxb_array_free(fxb_hash_map_values(H))), (fx_pfree(H)))

FxB_HashMap     *FxB_HashMap_create(            int length);
void            *fxb_hash_map_get(              FxB_HashMap *hash, char *key);
FxB_Node        *fxb_hash_map_get_node(         FxB_HashMap *hash, char *key);
void             fxb_hash_map_set(              FxB_HashMap *hash, char *key, void *value);
void             fxb_hash_map_free_list_values( FxB_HashMap *hash_map);
FxB_Array       *fxb_hash_map_keys(             FxB_HashMap *hash_map);
CHAR            *fxb_hash_map_inspect(          FxB_HashMap *hash_map);

#endif
