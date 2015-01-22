#ifndef __FxB_HashMap_h
#define __FxB_HashMap_h

#include "string.h"
#include "node.h"
#include "array.h"

#include "helpers.h"

typedef struct FxB_HashMap {
  int length;
  int capacity;
  FxB_Array *values;
} FxB_HashMap;

#define hash_map_values(H)            ((H)->values)
#define hash_map_list_at_index(H, I)  (array_at_index(hash_map_values(H), I))
#define hash_map_length(H)            ((H)->length)
#define hash_map_capacity(H)          ((H)->capacity)
#define hash_map_index_for_key(H, K)  (string_hash(K) % hash_map_capacity(H))
#define hash_map_free(H)              ((hash_map_free_list_values(H)), (array_free(hash_map_values(H))), (fx_pfree(H)))

FxB_HashMap     *FxB_HashMap_create(int length);
void            *hash_map_get(FxB_HashMap *hash, String *key);
Node            *hash_map_get_node(FxB_HashMap *hash, String *key);
void             hash_map_set(FxB_HashMap *hash, String *key, void *value);
void             hash_map_free_list_values(FxB_HashMap *hash_map);

#endif
