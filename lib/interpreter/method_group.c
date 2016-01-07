#include "method_group.h"

FxI_MethodGroup *FxI_MethodGroup_create(char *method_name) {
  FxI_MethodGroup *method_group = fx_alloc(FxI_MethodGroup);
  verify_memory(method_group);

  fxn_method_group_name(method_group) = method_name;

  FxB_List *functions = FxB_List_create();
  verify(functions);

  fxn_method_group_functions(method_group) = functions;

  return method_group;
error:
  if (method_group) { fx_pfree(method_group); }
  return NULL;
}
