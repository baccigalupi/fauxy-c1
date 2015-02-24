#include "class.h"
#include "method_group.h"

void fxn_class_set_method(FxN_Object *self, char *method_name, FxN_Function *function) {
  FxN_MethodGroup *method_group = NULL;

  method_group = fxn_class_get_method_group(self, method_name);

  if (!method_group) {
    method_group = FxN_MethodGroup_create(method_name);
    fxn_class_set_method_group(self, method_name, method_group);
  }

  fxn_method_group_push(method_group, function);
}
