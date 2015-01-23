#ifndef __FxI_Interpreter_h
#define __FxI_Interpreter_h 1

#include "../bricks/helpers.h"
#include "pool.h"

typedef struct FxI_Interpreter {
  // main event loop?
  // references to other loops
  FxI_Pool *pool;
} FxI_Interpreter;

#define fxi_interpreter_pool(I)       ((I)->pool)
#define fxi_interpreter_setup(I)      (fxi_interpreter_add_base_classes(I), fxi_interpreter_add_base_literals(I))
#define fxi_interpreter_free(I)       (fxi_pool_free(fxi_interpreter_pool(I)), fx_alloc(I))

FxI_Interpreter *FxI_Interpreter_create(int literal_capacity, int class_capacity, int lookup_capacity);
void             fxi_interpreter_add_base_classes(FxI_Interpreter *self);
void             fxi_interpreter_add_base_literals(FxI_Interpreter *self);

#endif
