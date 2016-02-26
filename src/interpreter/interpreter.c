#include "interpreter.h"
#include "expression_eval.h"
#include "object.h"
#include "../parser/expressions.h"
#include "../native/boolean_methods.h"

FxI_Interpreter *FxI_Interpreter_create(FxB_HashMap *config) {
  // literals, contexts, globals = first level of contexts, native registry
  FxI_NativeRegistry *registry = NULL;
  FxB_HashMap *literals = NULL;
  FxB_List *contexts = NULL;
  FxI_Object *global_space = NULL;

  FxI_Interpreter *self = fx_alloc(FxI_Interpreter);
  verify_memory(self);

  registry = FxB_HashMap_create(100);
  verify(registry);

  literals = FxB_HashMap_create(100);
  verify(literals);

  contexts = FxB_List_create();
  verify(contexts);

  global_space = FxI_Object_create(self, NULL);
  verify(global_space);
  fxb_list_push(contexts, global_space);

  fxi_interpreter_contexts(self) = contexts;
  fxi_interpreter_registry(self) = registry;
  fxi_interpreter_literals(self) = literals;

  return self;
error:
  if (self) { fx_pfree(self); }
  if (registry) { fxb_hash_map_free(registry); }
  if (literals) { fxb_hash_map_free(literals); }
  if (global_space) { fxi_object_free(global_space); }
  if (contexts) { fxb_list_free(contexts); }

  return NULL;
}

void fxi_interpreter_add_base_classes(FxI_Interpreter *self) {
  /*FxI_Class *object_class = FxI_Class_create("Object", NULL);*/
  // add native methods
  // add to global context

  // Setup classes
  // -------------
  // Object
  // Boolean
  // Integer
  // Float
  // String
  // EvalString
  // Function
  // Regex
  // Symbol
}

void fxi_interpreter_add_base_literals(FxI_Interpreter *self) {
  FxP_Expression *false_literal = FxP_Literal_create(NULL, TOKEN_FALSE);
  fxi_evaluate(self, false_literal);

  FxP_Expression *true_literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  fxi_evaluate(self, true_literal);
}

FxI_Object *fxi_lookup(FxI_Interpreter *self, char *key) {
  FxI_Object *object = NULL;
  FxI_Object *context = NULL;
  FxB_List   *contexts = fxi_interpreter_contexts(self);
  FxB_Node   *node =    fxb_list_node_last(contexts);

  while(!object && node) {
    context = fxb_node_value(node);
    verify(context);
    object = fxi_object_get_attribute(context, key);
    node = fxb_node_prev(node);
  }

  return object;
error:
  return NULL;
}

