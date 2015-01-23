#include "pool.h"

FxI_Pool *FxN_Pool_create(int literal_capacity, int class_capacity, int lookup_capacity) {
  FxB_HashMap *literals = NULL;
  FxB_HashMap *classes = NULL;
  FxB_HashMap *lookups = NULL;

  FxI_Pool *pool = fx_alloc(FxI_Pool);
  verify_memory(pool);

  literal_capacity =  literal_capacity ? literal_capacity : FXI_POOL_LITERAL_CAPACITY_DEFAULT;
  class_capacity =    class_capacity ? class_capacity :  FXI_POOL_CLASS_CAPACITY_DEFAULT;
  lookup_capacity =   lookup_capacity ? lookup_capacity :  FXI_POOL_LOOKUP_CAPACITY_DEFAULT;

  literals = FxB_HashMap_create(literal_capacity);
  verify(literals);
  fxi_pool_literals(pool) = literals;

  classes = FxB_HashMap_create(class_capacity);
  verify(classes);
  fxi_pool_classes(pool) = classes;

  lookups = FxB_HashMap_create(lookup_capacity);
  verify(lookups);
  fxi_pool_literals(pool) = lookups;

  return pool;
error:
  if (pool) { fx_pfree(pool); }
  if (literals) { fx_pfree(literals); }
  if (classes) { fx_pfree(classes); }

  return NULL;
}
