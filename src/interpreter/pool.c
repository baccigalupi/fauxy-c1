#include "pool.h"
#include "object.h"

FxI_Pool *FxI_Pool_create(FxB_HashMap *config) {
  FxB_HashMap *literals = NULL;
  FxB_HashMap *global_attributes = NULL;
  FxI_Object *globals  = NULL;

  FxI_Pool *pool = fx_alloc(FxI_Pool);
  verify_memory(pool);

  void *capacity_ref = fxb_hash_map_get(config, "literal_capacity");
  int literal_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_LITERAL_CAPACITY_DEFAULT;
  capacity_ref =       fxb_hash_map_get(config, "global_capacity");
  int global_capacity = capacity_ref ? *(int *)capacity_ref : FXI_POOL_GLOBAL_CAPACITY_DEFAULT;

  literals = FxB_HashMap_create(literal_capacity);
  verify(literals);
  fxi_pool_literals(pool) = literals;

  // Smaller version of the code for object create.
  // Classes, Objects and Globals are all objects so that
  // every possible context is an object
  globals = fx_alloc(FxI_Object);
  verify_memory(globals);
  global_attributes = FxB_HashMap_create(global_capacity);
  verify(global_attributes);
  fxi_object_attributes(globals) = global_attributes;

  fxi_pool_globals(pool) = globals;

  return pool;
error:
  if (pool) { fx_pfree(pool); }
  if (literals) { fxb_hash_map_free(literals); }
  if (global_attributes) { fxb_hash_map_free(global_attributes); }
  if (globals) { fxi_object_free(globals); }

  return NULL;
}
