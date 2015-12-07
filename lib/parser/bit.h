#ifndef __FxP_Bit
#define __FxP_Bit

typedef struct {
  int type;
  void *value;
} FxP_Bit;

#include "../bricks/_bricks.h"
#include "../types.h"

#include "lex_wrapper.h"
#include "parser_context.h"

#define fxp_bit_type(F)             ((F)->type)
#define fxp_bit_value(F)            ((F)->value)

#define fxp_bit_string__value(F)    ((FxB_String *)(fxp_bit_value(F)))
#define fxp_bit_number__value(F)    ((FxB_Number *)(fxp_bit_value(F)))

#define fxp_bit_string_value(F)       (fxb_string_value(         fxp_bit_string__value(F)))
#define fxb_bit_short_int_value(F)    (fxb_number_value_short(   fxp_bit_number__value(F)))
#define fxb_bit_standard_int_value(F) (fxb_number_value_standard(fxp_bit_number__value(F)))
#define fxb_bit_long_int_value(F)     (fxb_number_value_long(    fxp_bit_number__value(F)))
#define fxb_bit_llong_int_value(F)    (fxb_number_value_llong(   fxp_bit_number__value(F)))
#define fxb_bit_double_value(F)       (fxb_number_value_double(  fxp_bit_number__value(F)))
#define fxb_bit_ldouble_value(F)      (fxb_number_value_ldouble( fxp_bit_number__value(F)))

FxP_Bit        *FxP_Bit_string_create(char *text);
FxP_Bit        *FxP_Bit_integer_create(char *text);
FxP_Bit        *FxP_Bit_decimal_create(char *text);
FxP_Bit        *FxP_Bit_exponent_create(char *text);

char           *fx_trim_quote_char_text(char *original);
void            fxp_bit_free(FxP_Bit *bit);
FxB_String     *fxp_bit_inspect(FxP_Bit *bit);

#endif
