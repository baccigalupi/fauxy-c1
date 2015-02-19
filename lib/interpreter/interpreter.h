#ifndef __FxI_Interpreter_h
#define __FxI_Interpreter_h 1

#include "../bricks/helpers.h"
#include "../bricks/hash_map.h"
#include "pool.h"

typedef struct FxI_Interpreter {
  // main event loop?
  // references to other loops
  FxI_Pool *pool;
} FxI_Interpreter;

#define fxi_interpreter_pool(I)           ((I)->pool)
#define fxi_interpreter_free(I)           (fxi_pool_free(fxi_interpreter_pool(I)), fx_alloc(I))
#define fxi_interpreter_get_literal(I, K) (fxi_literal_get(fxi_interpreter_pool(I), K))
#define fxi_interpreter_get(I, K)         (fxi_context_current_get(fxi_interpreter_pool(I), K))

#define fxi_interpreter_literal_length(I)  (fxb_hash_map_length(fxi_pool_literals(fxi_interpreter_pool(I))))

#define fxi_interpreter_setup(I)          (fxi_interpreter_add_base_classes(I), fxi_interpreter_add_base_literals(I))

FxI_Interpreter *FxI_Interpreter_create(FxB_HashMap *config);
void             fxi_interpreter_add_base_classes(FxI_Interpreter *self);
void             fxi_interpreter_add_base_literals(FxI_Interpreter *self);

#endif
