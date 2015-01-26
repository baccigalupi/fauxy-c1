#include "interpreter.h"
#include "pool.h"
#include "object.h"
#include "../parser/expressions.h"
#include "../native/boolean.h"


FxI_Interpreter *FxI_Interpreter_create(int literal_capacity, int class_capacity, int lookup_capacity) {
  FxI_Interpreter *self = fx_alloc(FxI_Interpreter);
  verify_memory(self);

  FxI_Pool *pool = FxI_Pool_create(literal_capacity, class_capacity, lookup_capacity);
  verify(pool);
  fxi_interpreter_pool(self) = pool;

  return self;
error:
  if (self) { fx_pfree(self); }
  return NULL;
}

void fxi_interpreter_add_base_classes(FxI_Interpreter *self) {
  FxI_Pool *pool = fxi_interpreter_pool(self);

  // do stuff to setup classes
  // Boolean
  // Nil
  // Integer
  // Float
  // String
  // EvalString
  // Function
  // Regex
  // Symbol ??
}

void fxi_interpreter_add_base_literals(FxI_Interpreter *self) {
  FxI_Pool *pool = fxi_interpreter_pool(self);

  // Booleans ---------
  FxP_Expression *false_literal = FxP_Literal_create(NULL, TOKEN_FALSE);
  FxN_Object *false_object = FxN_Boolean_create(pool, false_literal);

  FxP_Expression *true_literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  FxN_Object *true_object = FxN_Boolean_create(pool, true_literal);

  fxi_literal_set(pool, "false", false_object);
  fxi_literal_set(pool, "true", true_object);

  // Nil ---------

}
