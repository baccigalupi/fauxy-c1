#ifndef __FxI_Pool
#define __FxI_Pool 1

#include "../bricks/hash_map.h"
#include "../bricks/list.h"
#include "../bricks/helpers.h"

#define FXI_POOL_LITERAL_CAPACITY_DEFAULT  400
#define FXI_POOL_GLOBAL_CAPACITY_DEFAULT    200

// Garbage managment: ??
//   * New allocations end up in the literals
//     for stuff that is part of the source code
//   * Otherwise it ends up in 'all', which is a list
//   * Global assignments go into the 'globals' hash
//
// Generational-ish-ness:
//   * Things that survive a generation can be moved to the back of the list
//   * Thing that are known to go out of scope can be bumped to the front
//   * Algorithm that figures out how far to go into list
//   * All of this collection happens in a background event loop?
//
// Defragmentation ... not really covered for now.

typedef struct FxI_Pool {
  FxB_HashMap *literals;
  FxB_List    *all;
  FxB_HashMap *globals;
} FxI_Pool;


#define fxi_pool_literals(P)        ((P)->literals)
#define fxi_pool_all(P)             ((P)->all)
#define fxi_pool_globals(P)         ((P)->globals)

#define fxi_pool_literal_get(P, K)       (fxb_hash_map_get(fxi_pool_literals(P), K))
#define fxi_pool_literal_set(P, K, V)    (fxb_hash_map_set(fxi_pool_literals(P), K, V))

#define fxi_pool_global_get(P, K)       (fxb_hash_map_get(fxi_pool_globals(P), K))
#define fxi_pool_global_set(P, K, V)    (fxb_hash_map_set(fxi_pool_globals(P), K, V))

#define fxi_pool_free(P)            (fx_pfree(P)) // TODO: more better

FxI_Pool *FxI_Pool_create(FxB_HashMap *config);

#endif
