#include "class.h"
#include "object.h"
#include "method_group.h"

void fxi_class_set_method(FxI_Object *self, char *method_name, FxI_FunctionDefinition *function) {
  FxI_MethodGroup *method_group = NULL;

  method_group = fxi_class_get_method_group(self, method_name);

  if (!method_group) {
    method_group = FxI_MethodGroup_create(method_name);
    fxi_class_set_method_group(self, method_name, method_group);
  }

  fxi_method_group_push(method_group, function);
}

FxI_Class *FxI_Class_create(FxI_Interpreter *interpreter, char *original_name, FxI_Class *superclass) {
  FxI_Object *klass = FxI_Object_create(interpreter, superclass);
  verify(klass);

  char *name = calloc(strlen(original_name) + 1, sizeof(char));
  verify_memory(name);
  strcpy(name, original_name);
  fxi_object__value(klass) = name;

  return klass;
error:
  if (klass) { fx_pfree(klass); }
  return NULL;
}
