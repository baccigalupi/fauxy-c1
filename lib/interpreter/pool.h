#ifndef __FxI_Pool
#define __FxI_Pool 1

#include "../bricks/hash_map.h"
#include "../bricks/list.h"
#include "../bricks/helpers.h"

#define FXI_POOL_LITERAL_CAPACITY_DEFAULT  400
#define FXI_POOL_CLASS_CAPACITY_DEFAULT    200
#define FXI_POOL_LOOKUP_CAPACITY_DEFAULT   1000

typedef struct FxI_Pool {
  FxB_HashMap *literals;
  FxB_List *contexts;
} FxI_Pool;

#define fxi_pool_literals(P)        ((P)->literals)
#define fxi_literal_get(P, K)       (fxb_hash_map_get(fxi_pool_literals(P), K))
#define fxi_literal_set(P, K, V)    (fxb_hash_map_set(fxi_pool_literals(P), K, V))

#define fxi_pool_contexts(P)              ((P)->contexts)
#define fxi_pool_context_current(P)       ((FxB_HashMap *)fxb_list_last(fxi_pool_contexts(P)))
#define fxi_pool_contexts_push(P, V)      (fxb_list_push(fxi_pool_contexts(P), V))
#define fxi_context_current_get(P, K)     (fxb_hash_map_get(fxi_pool_context_current(P), K))
#define fxi_context_current_set(P, K, V)  (fxb_hash_map_set(fxi_pool_context_current(P), K, V))
#define fxi_context_global(P)             (fxb_list_first(fxi_pool_contexts(P)))

#define fxi_pool_free(P)                  (fx_pfree(P)) // TODO: more better

FxI_Pool *FxI_Pool_create(int literal_capacity, int class_capacity, int lookup_capacity);

#endif
