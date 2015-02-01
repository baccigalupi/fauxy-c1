#ifndef __FxB_Integer_h
#define __FxB_Integer_h 1

#include "helpers.h"
#include <limits.h>

typedef struct FxB_Integer {
  int type;
  void *value;
} FxB_Integer;

#define fxb_integer_type(I)         ((I)->type)
#define fxb_integer_value(I)        ((I)->value)

#define fxb_integer_value_short(I)    (*(short    *)(fxb_integer_value(I)))
#define fxb_integer_value_standard(I) (*(int      *)(fxb_integer_value(I)))
#define fxb_integer_value_long(I)     (*(long     *)(fxb_integer_value(I)))
#define fxb_integer_value_llong(I)    (*(long long*)(fxb_integer_value(I)))

#define fxb_integer_free_husk(I)    (fx_pfree(I))

#define fxb_integer_create_value(I, TYPE)   TYPE *value = fx_alloc(TYPE); \
                                            verify_memory(value);         \
                                            *value = (TYPE)int_value;     \
                                            fxb_integer_value(I) = value;

enum {
  FXB_INT_SHORT = 340,
  FXB_INT_STANDARD,
  FXB_INT_LONG,
  FXB_INT_LLONG
};

FxB_Integer *FxB_Integer_create();
FxB_Integer *FxB_Integer_from_string(char *str);


#endif
