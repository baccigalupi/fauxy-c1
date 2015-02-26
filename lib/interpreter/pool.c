#include "pool.h"
#include "object.h"

FxI_Pool *FxI_Pool_create(FxB_HashMap *config) {
  FxB_HashMap *literals = NULL;
  FxB_HashMap *global_attributes = NULL;
  FxB_HashMap *natives = NULL;
  FxB_List    *all = NULL;
  FxN_Object *globals  = NULL;

  FxI_Pool *pool = fx_alloc(FxI_Pool);
  verify_memory(pool);

  void *capacity_ref = fxb_hash_map_get(config, "literal_capacity");
  int literal_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_LITERAL_CAPACITY_DEFAULT;
  capacity_ref =       fxb_hash_map_get(config, "global_capacity");
  int global_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_GLOBAL_CAPACITY_DEFAULT;
  capacity_ref =       fxb_hash_map_get(config, "native_capacity");
  int native_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_NATIVE_CAPACITY_DEFAULT;

  literals = FxB_HashMap_create(literal_capacity);
  verify(literals);
  fxi_pool_literals(pool) = literals;

  natives = FxB_HashMap_create(native_capacity);
  verify(natives);
  fxi_pool_natives(pool) = natives;

  all = FxB_List_create();
  verify(all)
  fxi_pool_all(pool) = all;

  // Smaller version of the code for object create.
  // Classes, Objects and Globals are all objects so that
  // every possible context is an object
  globals = fx_alloc(FxN_Object);
  verify_memory(globals);
  fxn_object_type(globals) = FX_GLOBALS;
  global_attributes = FxB_HashMap_create(global_capacity);
  verify(global_attributes);
  fxn_object_attributes(globals) = global_attributes;

  fxi_pool_globals(pool) = globals;

  return pool;
error:
  if (pool) { fx_pfree(pool); }
  if (all) { fxb_list_free(all); }
  if (literals) { fxb_hash_map_free(literals); }
  if (natives)  { fxb_hash_map_free(natives); }
  if (global_attributes) { fxb_hash_map_free(global_attributes); }
  if (globals) { fxn_object_free(globals); }

  return NULL;
}
