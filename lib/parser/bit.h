#ifndef __FxBit
#define __FxBit

typedef struct {
  int type;
  int size;
  void *value;
} FxBit;

// Lots of this shit needs to be included because bits need to know about
// token types. Including parse.tab.h leads to a cascade of entangled shit
// where everything needs to be included here
#include "../bricks/helpers.h"
#include "../bricks/string.h"
#include "lex_wrapper.h"
#include "expressions.h"
#include "parse.tab.h"

enum {
  FX_BIT_STRING = 300,
  FX_BIT_SHORT,
  FX_BIT_LONG,
  FX_BIT_FLOAT,
  FX_BIT_LONG_FLOAT
};


#define FX_BIT_SIZE_LIMIT 5

#define fx_bit_type(F)           ((F)->type)
#define fx_bit_size(F)           ((F)->size)
#define fx_bit_size_is_small(I)  (I < FX_BIT_SIZE_LIMIT)
#define fx_bit_is_small(F)       (fx_bit_size_is_small(fx_bit_size(F)))

#define fx_bit_value(F)            ((F)->value)

#define fx_bit_string__value(F)     ((char *)fx_bit_value(F))
#define fx_bit_short__value(F)      ((short *)(fx_bit_value(F)))
#define fx_bit_long__value(F)       ((long long *)(fx_bit_value(F)))
#define fx_bit_float__value(F)      ((double *)(fx_bit_value(F)))

#define fx_bit_string_value(F)     fx_bit_string__value(F)
#define fx_bit_short_value(F)      *(fx_bit_short__value(F))
#define fx_bit_long_value(F)       *(fx_bit_long__value(F))
#define fx_bit_float_value(F)      *(fx_bit_float__value(F))



FxBit       *FxBit_create(int token_type, char *text);
int             FxBit_bit_type(int token_type, Boolean is_small);
Boolean         fx_bit_add_float_value(FxBit *bit, char *text);
// Boolean fx_bit_add_long_float_value(FxBit *bit, char *text);
Boolean         fx_bit_add_short_value(FxBit *bit, char *text);
Boolean         fx_bit_add_long_value(FxBit *bit, char *text);
Boolean         fx_bit_add_string_value(FxBit *bit, char *text);
Boolean         fx_trim_string_value(FxBit *bit, char *text);
void            fx_bit_free(FxBit *bit);
String         *fx_bit_inspect(FxBit *bit);
String         *fx_bit_value_inspect(FxBit *bit);

#endif
