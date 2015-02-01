#ifndef __FxB_Number_h
#define __FxB_Number_h 1

#include "helpers.h"
#include <limits.h>

typedef struct FxB_Number {
  int type;
  void *value;
} FxB_Number;

#define fxb_number_type(I)         ((I)->type)
#define fxb_number_value(I)        ((I)->value)

#define fxb_number_value_short(I)    (*(short    *)(fxb_number_value(I)))
#define fxb_number_value_standard(I) (*(int      *)(fxb_number_value(I)))
#define fxb_number_value_long(I)     (*(long     *)(fxb_number_value(I)))
#define fxb_number_value_llong(I)    (*(long long*)(fxb_number_value(I)))

#define fxb_number_free_husk(I)    (fx_pfree(I))

#define fxb_number_create_value(I, TYPE)    TYPE *value = fx_alloc(TYPE); \
                                            verify_memory(value);         \
                                            *value = (TYPE)int_value;     \
                                            fxb_number_value(I) = value;

enum {
  FXB_INT_SHORT = 340,
  FXB_INT_STANDARD,
  FXB_INT_LONG,
  FXB_INT_LLONG
};

FxB_Number *FxB_Number_create();
FxB_Number *FxB_Integer_from_string(char *str);


#endif
