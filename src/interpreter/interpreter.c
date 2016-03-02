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
  FxI_Class *klass;
  FxI_Class *object_class;

  klass = FxI_Class_create(self, "Class", NULL);
  fxi_context_set(self, "Class", klass);

  object_class = FxI_Class_create(self, "Object", klass);
  fxi_context_set(self, "Object", object_class);

  klass = FxI_Class_create(self, "Function", object_class);
  fxi_context_set(self, "Function", klass);

  klass = FxI_Class_create(self, "Arguments", object_class);
  fxi_context_set(self, "Arguments", klass);

  klass = FxI_Class_create(self, "Boolean", object_class);
  fxi_context_set(self, "Boolean", klass);

  klass = FxI_Class_create(self, "String", object_class);
  fxi_context_set(self, "String", klass);

  klass = FxI_Class_create(self, "EvalString", object_class);
  fxi_context_set(self, "EvalString", klass);

  klass = FxI_Class_create(self, "Regex", object_class);
  fxi_context_set(self, "Regex", klass);

  klass = FxI_Class_create(self, "Integer", object_class);
  fxi_context_set(self, "Integer", klass);

  klass = FxI_Class_create(self, "Decimal", object_class);
  fxi_context_set(self, "Decimal", klass);

  // TODO: verify and throw
}

void fxi_interpreter_add_base_literals(FxI_Interpreter *self) {
  FxI_Class *Boolean = fxi_lookup(self, "Boolean");

  // true
  FxI_Object *object = FxI_Object_create(self, Boolean);
  fxi_object__value(object) = FxP_Literal_create(FxP_Bit_string_create("true"), TOKEN_TRUE);
  fxi_context_set(self, "true", object);

  // false
  object = FxI_Object_create(self, Boolean);
  fxi_object__value(object) = FxP_Literal_create(FxP_Bit_string_create("false"), TOKEN_FALSE);
  fxi_context_set(self, "false", object);

  // TODO: verify stuff and throw
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

