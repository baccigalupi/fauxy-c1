#include "interpreter.h"
#include "expression_eval.h"
#include "pool.h"
#include "object.h"
#include "../parser/expressions.h"
#include "../native/boolean_methods.h"
#include "../native/nil_methods.h"


FxI_Interpreter *FxI_Interpreter_create(FxB_HashMap *config) {
  FxI_Interpreter *self = fx_alloc(FxI_Interpreter);
  verify_memory(self);

  FxI_Pool *pool = FxI_Pool_create(config);
  verify(pool);
  fxi_interpreter_pool(self) = pool;

  return self;
error:
  if (self) { fx_pfree(self); }
  return NULL;
}

void fxi_interpreter_add_base_classes(FxI_Interpreter *self) {
  FxI_Pool *pool = fxi_interpreter_pool(self);

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
