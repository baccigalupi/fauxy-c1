#ifndef __FxP_Bit
#define __FxP_Bit

typedef struct {
  int type;
  int size;
  void *value;
} FxP_Bit;

// Lots of this shit needs to be included because bits are part of the lex/parse
// process. Lex and Bison are pretty hopelessly nested together and therefore
// everything needs to be included here
#include "../bricks/helpers.h"
#include "../bricks/string.h"
#include "lex_wrapper.h"
#include "parser_context.h"
#include "tokens.h"

enum {
  FX_BIT_STRING = 300,
  FX_BIT_SHORT,
  FX_BIT_LONG,
  FX_BIT_FLOAT,
  FX_BIT_LONG_FLOAT
};


#define FX_BIT_SIZE_LIMIT 5

#define fxp_bit_type(F)           ((F)->type)
#define fxp_bit_size(F)           ((F)->size)
#define fxp_bit_size_is_small(I)  (I < FX_BIT_SIZE_LIMIT)
#define fxp_bit_is_small(F)       (fxp_bit_size_is_small(fxp_bit_size(F)))
#define fxp_bit_value(F)          ((F)->value)

#define fxp_bit_string__value(F)     ((char *)fxp_bit_value(F))
#define fxp_bit_short__value(F)      ((short *)(fxp_bit_value(F)))
#define fxp_bit_long__value(F)       ((long long *)(fxp_bit_value(F)))
#define fxp_bit_float__value(F)      ((double *)(fxp_bit_value(F)))

#define fxp_bit_string_value(F)     fxp_bit_string__value(F)
#define fxp_bit_short_value(F)      *(fxp_bit_short__value(F))
#define fxp_bit_long_value(F)       *(fxp_bit_long__value(F))
#define fxp_bit_float_value(F)      *(fxp_bit_float__value(F))



FxP_Bit        *FxP_Bit_create(int token_type, char *text);
int             FxP_Bit_bit_type(int token_type, Boolean is_small);
Boolean         fxp_bit_add_float_value(FxP_Bit *bit, char *text);
// Boolean fxp_bit_add_long_float_value(FxP_Bit *bit, char *text);
Boolean         fxp_bit_add_short_value(FxP_Bit *bit, char *text);
Boolean         fxp_bit_add_long_value(FxP_Bit *bit, char *text);
Boolean         fxp_bit_add_string_value(FxP_Bit *bit, char *text);
Boolean         fx_trim_string_value(FxP_Bit *bit, char *text);
void            fxp_bit_free(FxP_Bit *bit);
String         *fxp_bit_inspect(FxP_Bit *bit);
String         *fxp_bit_value_description(FxP_Bit *bit);

#endif
