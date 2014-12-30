#ifndef __FxP_Expression
#define __FxP_Expression 1

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
typedef FxP_Expression FxP_Method;
typedef FxP_Expression FxP_Grouped;
typedef FxP_Expression FxP_List;
typedef FxP_Expression FxP_MethodArguments;
typedef FxP_Expression FxP_FunctionArguments;
typedef FxP_Expression FxP_LocalAssign;
typedef FxP_Expression FxP_ColonExpression;

// IMPORTANT, this bit thing is a bitch and has to stay
// below the typedefs!
#include "bit.h"

#define FX_EXPRESSION_INITAL_SIZE 5

enum {
  FXP_ST_LITERAL = 320,
  FXP_ST_LOOKUP,
  FXP_ST_METHOD,
  FXP_ST_FUNCTION,
  FXP_ST_GROUPED,
  FXP_ST_LIST,
  FXP_ST_METHOD_ARGUMENTS, // may not need these distinctions, being a list in a method or block is enough
  FXP_ST_FUNCTION_ARGUMENTS,
  FXP_ST_LOCAL_ASSIGN,
  FXP_ST_COLON_EXPRESSION,
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

// Literals have value array [token_type, bit]
#define fxp_literal__type(E)           (array_get(fxp_expression_value(E), 0))
#define fxp_literal_type(E)            (*((int *)fxp_literal__type(E)))
#define fxp_literal_bit(E)             (FxP_Bit *)(array_get(fxp_expression_value(E), 1))

FxP_Literal *FxP_Literal_create(FxP_Bit *bit, int token_type);
void         fxp_literal_free(FxP_Literal *literal);

// Lookups are similar to literal, with value array [token_type, bit]
#define fxp_lookup__type(E)           (array_get(fxp_expression_value(E), 0))
#define fxp_lookup_type(E)            (*((int *)fxp_lookup__type(E)))
#define fxp_lookup_bit(E)             (FxP_Bit *)(array_get(fxp_expression_value(E), 1))
#define fxp_lookup_free(E)            fxp_literal_free(E)

FxP_Lookup  *FxP_Lookup_create(FxP_Bit *bit, int token_type);

// Block value array [arguments, expressions]
#define fxp_function_arguments(E)           (FxP_Expression *)(array_get(fxp_expression_value(E), 0))
#define fxp_function_set_arguments(E, V)    (array_set(fxp_expression_value(E), 0, V))
#define fxp_function_expressions(E)         (FxP_Expressions *)(array_get(fxp_expression_value(E), 1))
#define fxp_function_set_expressions(E, V)  (array_set(fxp_expression_value(E), 1, V))

FxP_Function *FxP_Function_create_no_args(FxP_Expressions *expressions);
FxP_Function *FxP_Function_create(FxP_Expressions *expressions, FxP_List *list);

// Method calls [receiver, method_name, method_arguments]
#define fxp_method_receiver(E)           (FxP_Expression *)(array_get(fxp_expression_value(E), 0))
#define fxp_method_set_receiver(E, V)    (array_set(fxp_expression_value(E), 0, V))
#define fxp_method_message(E)            (FxP_Expression *)(array_get(fxp_expression_value(E), 1))
#define fxp_method_set_message(E, V)     (array_set(fxp_expression_value(E), 1, V))
#define fxp_method_arguments(E)          (FxP_Expression *)(array_get(fxp_expression_value(E), 2))
#define fxp_method_set_arguments(E, V)   (array_set(fxp_expression_value(E), 2, V))
#define FxP_Method_create()               FxP_Expression_create(FXP_ST_METHOD)

FxP_Method *FxP_Method_create_implicit(FxP_Bit *message, FxP_Expression *argument);
FxP_Method *fxp_method_convert_implicit(FxP_Method *self, FxP_Expression *receivier);
FxP_Method *FxP_Method_create_no_args(FxP_Expression *receiver, FxP_Bit *message);
FxP_Method *FxP_Method_create_operator(FxP_Expression *receiver, FxP_Bit *message, FxP_Expression *argument);
FxP_Method *fxp_method_add_function_argument(FxP_Method *method, FxP_Function *function);

// Grouped expressions are lists with one value,
// they could be an actual paren-ed exp or a list of one element
FxP_Grouped *FxP_Grouped_create(FxP_Expression *value);

#define fxp_list_length(E)             (array_length(fxp_expression_value(E)))
#define fxp_list_get(E, I)             (array_get(fxp_expression_value(E), I))
#define fxp_list_set(E, I, V)          (array_set(fxp_expression_value(E), I, V))

FxP_List *fxp_list_convert(FxP_Grouped *group);
FxP_List *FxP_List_create_deferred();
FxP_List *FxP_List_create_double(FxP_Expression *first, FxP_Expression *second);
FxP_List *fxp_list_unshift(FxP_List *list, FxP_Expression *value);

FxP_MethodArguments *fxp_method_arguments_convert(FxP_Expression *expression);

// Local assignment: [variable, value]
FxP_LocalAssign     *FxP_LocalAssign_create(FxP_Lookup *lookup, FxP_Expression *expression);
#define fxp_local_assignment_variable(E)             (FxP_Lookup *)(array_get(fxp_expression_value(E), 0))
#define fxp_local_assignment_set_variable(E, V)      (array_set(fxp_expression_value(E), 0, V))
#define fxp_local_assignment_value(E)                (FxP_Lookup *)(array_get(fxp_expression_value(E), 1))
#define fxp_local_assignment_set_value(E, V)         (array_set(fxp_expression_value(E), 1, V))

// Local assignment: [variable, value]
FxP_ColonExpression *FxP_ColonExpression_create(FxP_Lookup *variable, FxP_Expression *value);
#define fxp_colon_expression_variable(E)             (FxP_Lookup *)(array_get(fxp_expression_value(E), 0))
#define fxp_colon_expression_set_variable(E, V)      (array_set(fxp_expression_value(E), 0, V))
#define fxp_colon_expression_value(E)                (FxP_Lookup *)(array_get(fxp_expression_value(E), 1))
#define fxp_colon_expression_set_value(E, V)         (array_set(fxp_expression_value(E), 1, V))


#endif
