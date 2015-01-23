#include "interpreter.h"
#include "pool.h"

FxI_Interpreter *FxI_Interpreter_create(int literal_capacity, int class_capacity, int lookup_capacity) {
  FxI_Interpreter *self = fx_alloc(FxI_Interpreter);
  verify_memory(self);

  FxI_Pool *pool = FxI_Pool_create(literal_capacity, class_capacity, lookup_capacity);
  verify(pool);

  return self;
error:
  if (self) { fx_pfree(self); }
  return NULL;
}

void fxi_interpreter_add_base_classes(FxI_Interpreter *self) {
  
}

void fxi_interpreter_add_base_literals(FxI_Interpreter *self) {
  
}
