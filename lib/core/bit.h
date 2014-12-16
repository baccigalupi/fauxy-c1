#ifndef __FauxyBit
#define __FauxyBit


enum {
  FX_BIT_STRING = 300,
  FX_BIT_SHORT,
  FX_BIT_LONG,
  FX_BIT_FLOAT,
  FX_BIT_LONG_FLOAT
};


typedef struct {
  int type;
  int size;
  void *value;
} FauxyBit;

#include "../bricks/helpers.h"
#include "../parser/parser_state.h"
#include "../parser/parse.tab.h"

#define FX_BIT_SIZE_LIMIT 5

#define fauxy_bit_type(F)           ((F)->type)
#define fauxy_bit_size(F)           ((F)->size)
#define fauxy_bit_size_is_small(I)  (I < FX_BIT_SIZE_LIMIT)
#define fauxy_bit_is_small(F)       (fauxy_bit_size_is_small(fauxy_bit_size(F)))

#define fauxy_bit_value(F)            ((F)->value)

#define fauxy_bit_string__value(F)     ((char *)fauxy_bit_value(F))
#define fauxy_bit_short__value(F)      ((short *)(fauxy_bit_value(F)))
#define fauxy_bit_long__value(F)       ((long long *)(fauxy_bit_value(F)))
#define fauxy_bit_float__value(F)      ((double *)(fauxy_bit_value(F)))

#define fauxy_bit_string_value(F)     fauxy_bit_string__value(F)
#define fauxy_bit_short_value(F)      *(fauxy_bit_short__value(F))
#define fauxy_bit_long_value(F)       *(fauxy_bit_long__value(F))
#define fauxy_bit_float_value(F)      *(fauxy_bit_float__value(F))



FauxyBit       *FauxyBit_create(int token_type, char *text);
int             FauxyBit_bit_type(int token_type, Boolean is_small);
Boolean         fauxy_bit_add_float_value(FauxyBit *bit, char *text);
// Boolean fauxy_bit_add_long_float_value(FauxyBit *bit, char *text);
Boolean         fauxy_bit_add_short_value(FauxyBit *bit, char *text);
Boolean         fauxy_bit_add_long_value(FauxyBit *bit, char *text);
Boolean         fauxy_bit_add_string_value(FauxyBit *bit, char *text);
void            fauxy_bit_free(FauxyBit *bit);

#endif
