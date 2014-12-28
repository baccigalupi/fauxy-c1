#ifndef __fauxy_expression
#define __fauxy_expression 1

#include <stdlib.h>

#include "../bricks/string.h"
#include "../bricks/array.h"

typedef struct FxP_Expression {
  int type;
  Array *value;
} FxP_Expression;

typedef FxP_Expression FxP_Expressions;
typedef FxP_Expression FxP_Literal;
typedef FxP_Expression FxP_Lookup;
typedef FxP_Expression FxP_Function;
typedef FxP_Expression FxP_MethodCall;
typedef FxP_Expression FxP_GroupedExpression;
typedef FxP_Expression FxP_List;
typedef FxP_Expression FxP_ArgumentList;

// IMPORTANT, this bit thing is a bitch and has to stay
// below the typedefs!
#include "bit.h"

#define FX_EXPRESSION_INITAL_SIZE 5

enum {
  FXP_ST_LITERAL = 320,
  FXP_ST_LOOKUP,
  FXP_ST_BLOCK,
  FXP_ST_GROUPED,
  FXP_ST_LIST,
  FXP_ST_ARG_LIST,
  FXP_ST_METHOD,
  FXP_ST_LOCAL_ASSIGN,
  FXP_ST_ATTR_ASSIGN,
  FXP_ST_EXPORT,
  FXP_ST_EXPRESSIONS
}; // statement types


#define fxp_expression_type(E)        ((E)->type)
#define fxp_expression_value(E)       ((E)->value)
#define fxp_expression_length(E)      (array_length(fxp_expression_value(E)))
#define fxp_expression_push(E, V)     (array_push(fxp_expression_value(E), V))

FxP_Expression *FxP_Expression_create(int type);
void            fxp_expression_free(FxP_Expression *expression);

// Expressions are a type of expression!
// value array is the list of sub expressions
FxP_Expressions *FxP_Expressions_create();
void             fxp_expressions_free(FxP_Expressions *expressions);

FxP_Expression *FxP_TypedExpression_create(FxP_Bit *bit, int type, int token_type);
String         *fxp_typed_expression_inspect(FxP_Expression *expression, String *description, String *preface);

// Literals have value array [token_type, bit]
#define fxp_literal__type(E)           (array_get(fxp_expression_value(E), 0))
#define fxp_literal_type(E)            (*((int *)fxp_literal__type(E)))
#define fxp_literal_bit(E)             (FxP_Bit *)(array_get(fxp_expression_value(E), 1))

FxP_Literal *FxP_Literal_create(FxP_Bit *bit, int token_type);
String      *fxp_literal_inspect(FxP_Literal *literal);
String      *fxp_literal_description(FxP_Literal *literal);
void         fxp_literal_free(FxP_Literal *literal);

// Lookups are similar to literal, with value array [token_type, bit]
#define fxp_lookup__type(E)           (array_get(fxp_expression_value(E), 0))
#define fxp_lookup_type(E)            (*((int *)fxp_lookup__type(E)))
#define fxp_lookup_bit(E)             (FxP_Bit *)(array_get(fxp_expression_value(E), 1))
#define fxp_lookup_free(E)            fxp_literal_free(E)

FxP_Lookup  *FxP_Lookup_create(FxP_Bit *bit, int token_type);
String      *fxp_lookup_inspect(FxP_Lookup *literal);
String      *fxp_lookup_description(FxP_Lookup *literal);

// Block value array [arguments, expressions]
#define fxp_function_arguments(E)     (FxP_Expression *)(array_get(fxp_expression_value(E), 0))
#define fxp_function_expressions(E)   (FxP_Expressions *)(array_get(fxp_expression_value(E), 1))

// Method calls [receiver, method_name, argument_list]
#define fxp_method_receiver(E)           (FxP_Expression *)(array_get(fxp_expression_value(E), 0))
#define fxp_method_set_receiver(E, V)    (array_set(fxp_expression_value(E), 0, V))
#define fxp_method_message(E)            (FxP_Expression *)(array_get(fxp_expression_value(E), 1))
#define fxp_method_set_message(E, V)     (array_set(fxp_expression_value(E), 1, V))
#define fxp_method_arguments(E)          (FxP_Expression *)(array_get(fxp_expression_value(E), 2))
#define fxp_method_set_arguments(E, V)   (array_set(fxp_expression_value(E), 2, V))
#define FxP_MethodCall_create()           FxP_Expression_create(FXP_ST_METHOD)

FxP_MethodCall *FxP_MethodCall_create_implicit(FxP_Bit *message, FxP_Expression *argument);
FxP_MethodCall *fxp_method_call_convert_implicit(FxP_MethodCall *self, FxP_Expression *receivier);
FxP_MethodCall *FxP_MethodCall_create_no_args(FxP_Expression *receiver, FxP_Bit *message);
FxP_MethodCall *FxP_MethodCall_create_operator(FxP_Expression *receiver, FxP_Bit *message, FxP_Expression *argument);
FxP_MethodCall *fxp_method_call_add_function_argument(FxP_MethodCall *method, FxP_Function *function);


// Grouped expressions are lists with one value,
// they could be an actual paren-ed exp or a list of one element
FxP_GroupedExpression *FxP_GroupedExpression_create(FxP_Expression *value);

#define fxp_list_length(E)             (array_length(fxp_expression_value(E)))
#define fxp_list_get(E, I)             (array_get(fxp_expression_value(E), I))
#define fxp_list_set(E, I, V)          (array_set(fxp_expression_value(E), I, V))

FxP_List *fxp_list_convert(FxP_GroupedExpression *group);
FxP_List *FxP_List_create_deferred();
FxP_List *FxP_List_create_double(FxP_Expression *first, FxP_Expression *second);
FxP_List *fxp_list_unshift(FxP_List *list, FxP_Expression *value);

FxP_ArgumentList *fxp_argument_list_convert(FxP_Expression *expression);

#endif
