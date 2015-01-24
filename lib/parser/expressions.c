#include "../bricks/helpers.h"
#include "expressions.h"

FxP_Expression *FxP_Expression_create(int type) {
  FxP_Expression *expression = fx_alloc(FxP_Expression);
  verify_memory(expression);

  FxB_Array *value = FxB_Array_create(4);
  verify_memory(value);

  fxp_expression_type(expression) = type;
  fxp_expression_value(expression) = value;

  return expression;
error:
  if (expression) { fx_pfree(expression); }
  return NULL;
}

void fxp_expression_free(void *void_expression) {
  if (!void_expression) {
    return;
  }

  FxP_Expression *expression = void_expression;
  int type = fxp_expression_type(expression);

  if (type == FXP_ST_LITERAL || type == FXP_ST_LOOKUP) {
    fxp_expression_free_typed_guts(expression);
  } else {
    fxb_array_each(fxp_expression_value(expression), fxp_expression_free);
  }

  fxp_expression_free_husk(expression);
}

void fxp_expression_free_husk(FxP_Expression *expression) {
  fxb_array_free(fxp_expression_value(expression));
  fx_pfree(expression);
}

void fxp_expression_free_typed_guts(FxP_Expression *expression) {
  fx_pfree(fxp_typed__type(expression));
  fxp_bit_free(fxp_typed_bit(expression));
}

FxP_Expressions *FxP_Expressions_create() {
  FxP_Expression *expressions = FxP_Expression_create(FXP_ST_EXPRESSIONS);
  verify(expressions);
  return expressions;
error:
  return NULL;
}

FxP_Expression *FxP_TypedExpression_create(FxP_Bit *bit, int exp_type, int token_type) {
  FxP_Expression *expression = FxP_Expression_create(exp_type);
  verify_memory(expression);

  FxB_Array *values = fxp_expression_value(expression);
  int *type = fx_alloc(int);
  *type = token_type;
  fxb_array_push(values, type);
  fxb_array_push(values, bit);

  return expression;
error:
  return NULL;
}

FxP_Expression *FxP_Literal_create(FxP_Bit *bit, int token_type) {
  FxP_Expression *literal = FxP_TypedExpression_create(bit, FXP_ST_LITERAL, token_type);
  verify(literal);
  return literal;
error:
  return NULL;
}

FxP_Lookup *FxP_Lookup_create(FxP_Bit *bit, int token_type) {
  FxP_Expression *lookup = FxP_TypedExpression_create(bit, FXP_ST_LOOKUP, token_type);
  verify(lookup);

  return lookup;
error:
  return NULL;
}

FxP_Method *FxP_Method_create_implicit(FxP_Literal *method_name, FxP_Expression *argument) {
  FxP_Expression *arguments = NULL;
  FxP_Method *call = FxP_Method_create();
  verify(call);

  fxp_method_set_message(call, method_name);
  if (fxp_expression_type(argument) == FXP_ST_LIST || fxp_expression_type(argument) == FXP_ST_GROUPED) {
    arguments = argument;
    fxp_expression_type(arguments) = FXP_ST_METHOD_ARGUMENTS;
  } else {
    arguments = FxP_Expression_create(FXP_ST_METHOD_ARGUMENTS);
    verify(arguments);
    fxp_list_push(arguments, argument);
  }
  fxp_method_set_arguments(call, arguments);

  return call;
error:
  if (call) { fxp_expression_free(call); }
  return NULL;
}

FxP_Method *fxp_method_convert_implicit(FxP_Method *self, FxP_Expression *receiver) {
  fxp_method_set_receiver(self, receiver);
  return self;
}

FxP_Method *fxp_method_add_function_argument(FxP_Method *method, FxP_Function *function) {
  FxP_MethodArguments *list;

  if (fxp_expression_length(method) == 2) {
    list = FxP_Expression_create(FXP_ST_METHOD_ARGUMENTS);
    verify(list);
    fxp_method_set_arguments(method, list);
  }

  list = fxp_method_arguments(method);
  fxp_list_push(list, function);

  return method;
error:
  return NULL;
}

FxP_Method *FxP_Method_create_no_args(FxP_Expression *receiver, FxP_Literal *message) {
  FxP_Method *method = FxP_Method_create();
  verify_memory(method);

  fxp_method_set_receiver(method, receiver);
  fxp_method_set_message(method, message);

  return method;
error:
  return NULL;
}

FxP_Method *FxP_Method_create_args(FxP_Expression *receiver, FxP_Literal *message, FxP_Expression *argument) {
  FxP_MethodArguments *list = fxp_method_arguments_convert(argument);
  verify(list);

  FxP_Method *method = FxP_Method_create();
  verify(method);

  fxp_method_set_receiver(method, receiver);
  fxp_method_set_message(method, message);
  fxp_method_set_arguments(method, list);

  return method;
error:
  if (list) { fxp_expression_free(list); }
  return NULL;
}

FxP_Grouped *FxP_Grouped_create(FxP_Expression *value) {
  FxP_Grouped *group = FxP_Expression_create(FXP_ST_GROUPED);
  verify_memory(group);

  if (value) {
    fxp_expression_push(group, value);
  }
  return group;
error:
  return NULL;
}

FxP_FxB_List *fxp_list_convert(FxP_Grouped *group) {
  fxp_expression_type(group) = FXP_ST_LIST;
  return group;
}

FxP_FxB_List *FxP_FxB_List_create_deferred() {
  FxP_Literal *value = FxP_Literal_create(NULL, TOKEN_DEFERRED_ARGUMENT);
  verify(value);

  FxP_FxB_List *list = FxP_Expression_create(FXP_ST_LIST);
  verify(list);
  fxp_expression_push(list, value);

  return list;
error:
  if (value) { fxp_expression_free(value); }
  return NULL;
}

FxP_FxB_List *FxP_FxB_List_create_double(FxP_Expression *first, FxP_Expression *second) {
  FxP_FxB_List *list = FxP_Expression_create(FXP_ST_LIST);
  verify(list);

  fxp_expression_push(list, second);
  fxp_expression_push(list, first);

  return list;
error:
  return NULL;
}

FxP_MethodArguments *fxp_method_arguments_convert(FxP_Expression *expression) {
  FxP_MethodArguments *list = NULL;
  int type = fxp_expression_type(expression);

  if (type == FXP_ST_LIST || type == FXP_ST_GROUPED) {
    list = expression;
  } else {
    list = FxP_Grouped_create(expression);
    verify(list);
  }

  fxp_expression_type(list) = FXP_ST_METHOD_ARGUMENTS;
  return list;
error:
  return NULL;
}

FxP_Function *FxP_Function_create_no_args() {
  FxP_Function *function = NULL;
  FxP_Expressions *expressions = FxP_Expression_create(FXP_ST_EXPRESSIONS);
  verify(expressions);

  function = FxP_Expression_create(FXP_ST_FUNCTION);
  verify(function);

  fxp_function_set_expressions(function, expressions);

  return function;
error:
  if (function) { fx_pfree(function); }
  return NULL;
}

FxP_Function *FxP_Function_create(FxP_FxB_List *list) {
  FxP_Function *function = FxP_Function_create_no_args();
  verify(function);

  fxp_expression_type(list) = FXP_ST_FUNCTION_ARGUMENTS;
  fxp_function_set_arguments(function, list);

  return function;
error:
  return NULL;
}

FxP_LocalAssign *FxP_LocalAssign_create(FxP_Lookup *variable, FxP_Expression *value) {
  FxP_Function *local = FxP_Expression_create(FXP_ST_LOCAL_ASSIGN);
  verify(local);

  fxp_expression_set_left(local, variable);
  fxp_expression_set_right(local, value);

  return local;
error:
  return NULL;
}

FxP_LocalAssign *FxP_ColonExpression_create(FxP_Lookup *variable, FxP_Expression *value) {
  FxP_Function *colon = FxP_Expression_create(FXP_ST_COLON_EXPRESSION);
  verify(colon);

  fxp_expression_set_left(colon, variable);
  fxp_expression_set_right(colon, value);

  return colon;
error:
  return NULL;
}
