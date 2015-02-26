#include "interpreter.h"
#include "expression_eval.h"
#include "pool.h"
#include "object.h"
#include "../parser/expressions.h"
#include "../native/boolean_methods.h"
#include "../native/nil_methods.h"


FxI_Interpreter *FxI_Interpreter_create(FxB_HashMap *config) {
  FxI_Pool *pool = NULL;
  FxI_Interpreter *self = fx_alloc(FxI_Interpreter);
  verify_memory(self);

  pool = FxI_Pool_create(config);
  verify(pool);
  fxi_interpreter_pool(self) = pool;

  FxB_List *contexts = FxB_List_create();
  verify(contexts);
  fxb_list_push(contexts, fxi_pool_globals(pool));
  fxi_interpreter_contexts(self) = contexts;

  return self;
error:
  if (self) { fx_pfree(self); }
  if (pool) { fxi_pool_free(pool); }
  return NULL;
}

void fxi_interpreter_add_base_classes(FxI_Interpreter *self) {
  /*FxN_Class *object_class = FxN_Class_create("Object", NULL);*/
  // add native methods
  // add to global context

  // Setup classes
  // -------------
  // Object
  // Boolean
  // Nil
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

  FxP_Expression *nil_literal = FxP_Literal_create(NULL, TOKEN_NIL);
  fxi_evaluate(self, nil_literal);
}

FxN_Object *fxi_lookup(FxI_Interpreter *self, char *key) {
  FxN_Object *object = NULL;
  FxN_Object *context = NULL;
  FxB_List   *contexts = fxi_interpreter_contexts(self);
  FxB_Node   *node =    fxb_list_node_last(contexts);

  while(!object && node) {
    context = node_value(node);
    verify(context);
    object = fxn_object_get_attribute(context, key);
    node = node_prev(node);
  }

  return object;
error:
  return NULL;
}

