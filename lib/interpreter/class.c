#include "class.h"
#include "object.h"
#include "method_group.h"

FxN_Class *FxN_Class_create(char *name, FxN_Class *super_class) {
  FxN_Class *self = fx_alloc(FxN_Class);
  verify_memory(self);

  fxn_class_name(self) = name;
  fxn_class_super_class(self) = super_class;

  FxB_HashMap *methods = FxB_HashMap_create(FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE);
  verify(methods);
  fxn_class_methods(self) = methods;

  return self;
error:
  if (self) { fx_pfree(self); }
  return NULL;
}

void fxn_class_set_method(FxN_Class *self, char *method_name, FxN_Function *function) {
  FxN_MethodGroup *method_group = NULL;

  method_group = fxn_class_get_method_group(self, method_name);

  if (!method_group) {
    method_group = FxN_MethodGroup_create(method_name);
    fxn_class_set_method_group(self, method_name, method_group);
  }

  fxn_method_group_push(method_group, function);
}
