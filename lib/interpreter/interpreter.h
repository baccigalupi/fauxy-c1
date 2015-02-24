#ifndef __FxI_Interpreter_h
#define __FxI_Interpreter_h 1

#include "../bricks/helpers.h"
#include "../bricks/hash_map.h"
#include "../bricks/list.h"
#include "pool.h"

typedef struct FxI_Interpreter {
  // main event loop?
  // references to other loops
  FxI_Pool *pool;
  FxB_List *contexts;
} FxI_Interpreter;

#define fxi_interpreter_pool(I)           ((I)->pool)
#define fxi_interpreter_contexts(I)       ((I)->contexts)

#define fxi_interpreter_free(I)           (fxi_pool_free(fxi_interpreter_pool(I)), fx_alloc(I))

#define fxi_interpreter_literals(I)       (fxi_pool_literals(fxi_interpreter_pool(I)))
#define fxi_literal_get(I, K)             (fxi_pool_literal_get(fxi_interpreter_pool(I), K))
#define fxi_literal_set(I, K, V)          (fxi_pool_literal_set(fxi_interpreter_pool(I), K, V))
#define fxi_interpreter_literal_length(I) (fxb_hash_map_length(fxi_pool_literals(fxi_interpreter_pool(I))))

#define fxi_interpreter_globals(I)        (fxi_pool_globals(fxi_interpreter_pool(I)))
#define fxi_global_get(I, K)              (fxi_pool_global_get(fxi_interpreter_pool(I), K))
#define fxi_global_set(I, K, V)           (fxi_pool_global_set(fxi_interpreter_pool(I), K, V))
#define fxi_interpreter_global_length(I)  (fxb_hash_map_length(fxi_pool_globals(fxi_interpreter_pool(I))))

#define fxi_interpreter_setup(I)          (fxi_interpreter_add_base_classes(I), fxi_interpreter_add_base_literals(I))

#define fxi_lookup(I, K)                  (fxi_global_get(I, K)) // TODO: change to function with better chain lookup
#define fxi_context_set(I, K, V)          (fxi_global_set(I, K, V)) // TODO: set in current context

FxI_Interpreter *FxI_Interpreter_create(FxB_HashMap *config);
void             fxi_interpreter_add_base_classes(FxI_Interpreter *self);
void             fxi_interpreter_add_base_literals(FxI_Interpreter *self);

#endif
