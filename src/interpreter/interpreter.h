#ifndef __FxI_Interpreter_h
#define __FxI_Interpreter_h 1

#include "../bricks/_bricks.h"

#include "structs.h"

#define fxi_interpreter_contexts(I)       ((I)->contexts)
#define fxi_interpreter_registry(I)       ((I)->registry)

                                          // TODO: more better
#define fxi_interpreter_free(I)           (fxb_hash_map_free(fxi_interpreter_registry(I)), fx_pfree(I))
#define fxi_interpreter_setup(I)          (fxi_interpreter_add_base_classes(I), fxi_interpreter_add_base_literals(I))

#define fxi_current_context(I)              (FxI_Object *)(fxb_list_last(fxi_interpreter_contexts(I)))
#define fxi_interpreter_push_context(I, V)  (fxb_list_push(fxi_interpreter_contexts(I), V))
#define fxi_interpreter_pop_context(I)      (fxb_list_pop(fxi_interpreter_contexts(I)))
#define fxi_interpreter_globals(I)          (FxI_Object *)(fxb_list_first(fxi_interpreter_contexts(I)))

#define fxi_context_set(I, K, V)            (fxi_object_set_attribute(fxi_current_context(I), K, V))

#define fxi_boolean(I, T)   ((T) ? fxi_true(I) : fxi_false(I))
#define fxi_false(I)        (fxi_lookup(I, "false"))
#define fxi_true(I)         (fxi_lookup(I, "true"))

FxI_Interpreter *FxI_Interpreter_create();
void             fxi_interpreter_add_base_classes(FxI_Interpreter *self);
void             fxi_interpreter_add_base_literals(FxI_Interpreter *self);
FxI_Object      *fxi_lookup(FxI_Interpreter *self, char *key);

#endif
