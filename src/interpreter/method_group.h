#ifndef FxI_MethodGroup_h
#define FxI_MethodGroup_h 1

#include "../bricks/_bricks.h"

#include "structs.h"

#define fxi_method_group_name(C)        ((C)->name)
#define fxi_method_group_functions(C)   ((C)->functions)
#define fxi_method_group_free(C)        (fx_pfree(C)) // TODO: more better

#define fxi_method_group_push(C, V)     (fxb_list_push(fxi_method_group_functions(C), V))
#define fxi_method_group_length(C)      (fxb_list_length(fxi_method_group_functions(C)))

FxI_MethodGroup *FxI_MethodGroup_create(char *method_name);

#endif
