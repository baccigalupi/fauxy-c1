#include "pool.h"

FxI_Pool *FxI_Pool_create(FxB_HashMap *config) {
  FxB_HashMap *literals = NULL;
  FxB_List    *all = NULL;
  FxB_HashMap *globals  = NULL;

  FxI_Pool *pool = fx_alloc(FxI_Pool);
  verify_memory(pool);

  void *capacity_ref = fxb_hash_map_get(config, "literal_capacity");
  int literal_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_LITERAL_CAPACITY_DEFAULT;
  capacity_ref =       fxb_hash_map_get(config, "global_capacity");
  int global_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_GLOBAL_CAPACITY_DEFAULT;

  literals = FxB_HashMap_create(literal_capacity);
  verify(literals);
  fxi_pool_literals(pool) = literals;

  all = FxB_List_create();
  verify(all)
  fxi_pool_all(pool) = all;

  globals = FxB_HashMap_create(global_capacity);
  verify(globals);
  fxi_pool_globals(pool) = globals;

  return pool;
error:
  if (pool) { fx_pfree(pool); }
  if (all) { fxb_list_free(all); }
  if (literals) { fxb_hash_map_free(literals); }
  if (globals) { fxb_hash_map_free(globals); }

  return NULL;
}
