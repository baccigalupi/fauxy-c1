#ifndef __FauxyBit
#define __FauxyBit

#include "../bricks/helpers.h"

enum {
  FX_BIT_STRING = 300,
  FX_BIT_SHORT,
  FX_BIT_LONG,
  FX_BIT_FLOAT,
  FX_BIT_LONG_FLOAT
};

// Keep these in sync, with the create ... or :(

typedef struct {
  int type;
  int size;
  union {
    char        *as_string;
    short       *as_short;
    long long   *as_long;
    double      *as_float;
    long double *as_long_float;
  } value;
} FauxyBit;

#define FX_BIT_SIZE_LIMIT 5

#define fauxy_bit_type(F)           ((F)->type)
#define fauxy_bit_size(F)           ((F)->size)
#define fauxy_bit_size_is_small(I)  (I < FX_BIT_SIZE_LIMIT)
#define fauxy_bit_is_small(F)       (fauxy_bit_size_is_small(fauxy_bit_size(F)))

#define fauxy_bit_value(F)            ((F)->value)
#define fauxy_bit_string_value(F)     (fauxy_bit_value(F).as_string)
#define fauxy_bit_short_value(F)      (*(fauxy_bit_value(F).as_short))
#define fauxy_bit_long_value(F)       (*(fauxy_bit_value(F).as_long))
#define fauxy_bit_float_value(F)      (*(fauxy_bit_value(F).as_float))
#define fauxy_bit_long_float_value(F) (*(fauxy_bit_value(F).as_long_float))



FauxyBit        *FauxyBit_create(int token_type, char *text);
int     FauxyBit_bit_type(int token_type, Boolean is_small);
Boolean fauxy_bit_add_float_value(FauxyBit *bit, char *text);
Boolean fauxy_bit_add_long_float_value(FauxyBit *bit, char *text);
Boolean fauxy_bit_add_short_value(FauxyBit *bit, char *text);
Boolean fauxy_bit_add_long_value(FauxyBit *bit, char *text);
Boolean fauxy_bit_add_string_value(FauxyBit *bit, char *text);

#endif
