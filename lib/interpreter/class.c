#include "class.h"
#include "object.h"
#include "method_group.h"

void fxn_class_set_method(FxN_Object *self, char *method_name, FxN_FunctionDefinition *function) {
  FxN_MethodGroup *method_group = NULL;

  method_group = fxn_class_get_method_group(self, method_name);

  if (!method_group) {
    method_group = FxN_MethodGroup_create(method_name);
    fxn_class_set_method_group(self, method_name, method_group);
  }

  fxn_method_group_push(method_group, function);
}

FxN_Class *FxN_Class_create(FxI_Interpreter *interpreter, char *original_name, FxN_Class *superclass) {
  FxN_Object *klass = FxN_Object_create(interpreter, superclass);
  verify(klass);

  char *name = calloc(strlen(original_name) + 1, sizeof(char));
  verify_memory(name);
  strcpy(name, original_name);
  fxn_object__value(klass) = name;

  return klass;
error:
  if (klass) { fx_pfree(klass); }
  return NULL;
}
