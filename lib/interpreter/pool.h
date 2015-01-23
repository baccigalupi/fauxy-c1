#ifndef __FxI_Pool
#define __FxI_Pool 1

#include "../bricks/hash_map.h"
#include "../bricks/helpers.h"

#define FXI_POOL_LITERAL_CAPACITY_DEFAULT  400
#define FXI_POOL_CLASS_CAPACITY_DEFAULT    200
#define FXI_POOL_LOOKUP_CAPACITY_DEFAULT   1000

typedef struct FxI_Pool {
  FxB_HashMap *literals;
  FxB_HashMap *classes;
  FxB_HashMap *lookups;
} FxI_Pool;

#define fxi_pool_literals(P)        ((P)->literals)
#define fxi_literal_get(P, K)       (hash_map_get(fxi_pool_contants(P), K))
#define fxi_literal_set(P, K, V)    (hash_map_set(fxi_pool_contants(P), K, V))

#define fxi_pool_classes(P)         ((P)->classes)
#define fxi_class_get(P, K)         (hash_map_get(fxi_pool_classes(P), K))
#define fxi_class_set(P, K, V)      (hash_map_set(fxi_pool_classes(P), K, V))

#define fxi_pool_lookups(P)         ((P)->lookups)
#define fxi_lookup_get(P, K)        (hash_map_get(fxi_pool_lookups(P), K))
#define fxi_lookup_set(P, K, V)     (hash_map_set(fxi_pool_lookups(P), K, V))

#define fxn_pool_free(P)            (fx_pfree(P)) // TODO: more better

FxI_Pool   *FxN_Pool_create(int literal_capacity, int class_capacity, int lookup_capacity);

#endif
