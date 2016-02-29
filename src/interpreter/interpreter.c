#include "interpreter.h"
#include "expression_eval.h"
#include "object.h"
#include "class.h"
#include "../parser/expressions.h"
#include "../native/boolean_methods.h"

FxI_Interpreter *FxI_Interpreter_create() {
  // contexts, globals = first level of contexts, native registry
  FxI_NativeRegistry *registry = NULL;
  FxB_HashMap *literals = NULL;
  FxB_List *contexts = NULL;
  FxI_Object *global_space = NULL;

  FxI_Interpreter *self = fx_alloc(FxI_Interpreter);
  verify_memory(self);

  // TODO build these values from configuration in json
  registry = FxB_HashMap_create(100);
  verify(registry);

  contexts = FxB_List_create();
  verify(contexts);

  global_space = FxI_Object_create(self, NULL);
  verify(global_space);
  fxb_list_push(contexts, global_space);

  fxi_interpreter_contexts(self) = contexts;
  fxi_interpreter_registry(self) = registry;

  return self;
error:
  if (self) { fx_pfree(self); }
  if (registry) { fxb_hash_map_free(registry); }
  if (global_space) { fxi_object_free(global_space); }
  if (contexts) { fxb_list_free(contexts); }

  return NULL;
}

void fxi_interpreter_add_base_classes(FxI_Interpreter *self) {
  FxP_Bit        *lookup_bit;
  FxP_Lookup     *lookup;
  FxI_Class      *klass;
  // set class id on

  klass = FxI_Class_create(self, "Class", NULL);
  fxi_context_set(self, "Class", klass);

  klass = FxI_Class_create(self, "Object", NULL);
  fxi_context_set(self, "Object", klass);

  klass = FxI_Class_create(self, "Function", NULL);
  fxi_context_set(self, "Function", klass);

  klass = FxI_Class_create(self, "Arguments", NULL);
  fxi_context_set(self, "Arguments", klass);

  klass = FxI_Class_create(self, "Boolean", NULL);
  fxi_context_set(self, "Boolean", klass);

  // Setup classes
  // -------------
  // Integer
  // Decimal
  // String
  // EvalString
  // Regex
}

void fxi_interpreter_add_base_literals(FxI_Interpreter *self) {
  FxP_Lookup  *lookup;
  FxP_Expression *assignment;
  FxP_Bit *lookup_bit;
  FxP_Expression *literal;

  lookup_bit =     FxP_Bit_string_create("false");
  literal =        FxP_Literal_create(lookup_bit, TOKEN_FALSE);
  lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);
  assignment =     FxP_ColonExpression_create(lookup, literal);
  // free the stuff??

  fxi_evaluate_assignment(self, assignment);

  lookup_bit =     FxP_Bit_string_create("true");
  literal =        FxP_Literal_create(lookup_bit, TOKEN_TRUE);
  lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);
  assignment =     FxP_ColonExpression_create(lookup, literal);
  // more freeing?

  fxi_evaluate_assignment(self, assignment);

  // TODO: verify and return null exception
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

