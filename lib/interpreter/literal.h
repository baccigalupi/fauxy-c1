#ifndef __int_literal_h
#define __int_literal_h

#include "../parser/expressions.h"

#define fxi_object_value_short(O)           (fxb_bit_short_int_value(fxp_literal_bit(fxn_object_value(O))))
#define fxi_object_value_standard_int(O)    (fxb_bit_standard_int_value(fxp_literal_bit(fxn_object_value(O))))
#define fxi_object_value_long(O)            (fxb_bit_long_int_value(fxp_literal_bit(fxn_object_value(O))))
#define fxi_object_value_llong(O)           (fxb_bit_llong_int_value(fxp_literal_bit(fxn_object_value(O))))

#define fxi_object_value_double(O)     (fxb_bit_double_value(fxp_literal_bit(fxn_object_value(O))))
#define fxi_object_value_ldouble(O)    (fxb_bit_ldouble_value(fxp_literal_bit(fxn_object_value(O))))

char *fxi_literal_key(FxP_Literal *literal);

#endif
