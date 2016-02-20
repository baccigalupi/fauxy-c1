#ifndef __FxI_Interpreter_h
#define __FxI_Interpreter_h 1

#include "../bricks/_bricks.h"

#include "structs.h"
#include "pool.h"

#define fxi_interpreter_pool(I)           ((I)->pool)
#define fxi_interpreter_contexts(I)       ((I)->contexts)
#define fxi_interpreter_registry(I)       ((I)->registry)

#define fxi_interpreter_free(I)           (fxi_pool_free(fxi_interpreter_pool(I)), fxb_hash_map_free(fxi_interpreter_registry(I)), fx_pfree(I))

#define fxi_interpreter_literals(I)       (fxi_pool_literals(fxi_interpreter_pool(I)))
#define fxi_literal_get(I, K)             (fxi_pool_literal_get(fxi_interpreter_pool(I), K))
#define fxi_literal_set(I, K, V)          (fxi_pool_literal_set(fxi_interpreter_pool(I), K, V))
#define fxi_interpreter_literal_length(I) (fxb_hash_map_length(fxi_pool_literals(fxi_interpreter_pool(I))))

#define fxi_interpreter_globals(I)        (fxi_pool_globals(fxi_interpreter_pool(I)))
#define fxi_global_get(I, K)              (fxi_pool_global_get(fxi_interpreter_pool(I), K))
#define fxi_global_set(I, K, V)           (fxi_pool_global_set(fxi_interpreter_pool(I), K, V))
#define fxi_interpreter_global_length(I)  (fxb_hash_map_length(fxi_pool_globals(fxi_interpreter_pool(I))))

#define fxi_interpreter_setup(I)          (fxi_interpreter_add_base_classes(I), fxi_interpreter_add_base_literals(I))

#define fxi_current_context(I)              (FxI_Object *)(fxb_list_last(fxi_interpreter_contexts(I)))
#define fxi_interpreter_push_context(I, V)  (fxb_list_push(fxi_interpreter_contexts(I), V))
#define fxi_interpreter_pop_context(I)      (fxb_list_pop(fxi_interpreter_contexts(I)))

#define fxi_context_set(I, K, V)            (fxi_object_set_attribute(fxi_current_context(I), K, V))

FxI_Interpreter *FxI_Interpreter_create(FxB_HashMap *config);
void             fxi_interpreter_add_base_classes(FxI_Interpreter *self);
void             fxi_interpreter_add_base_literals(FxI_Interpreter *self);
FxI_Object      *fxi_lookup(FxI_Interpreter *self, char *key);

#endif
