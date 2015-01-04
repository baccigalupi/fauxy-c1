#include "../bricks/helpers.h"
#include "expressions.h"

FxP_Expression *FxP_Expression_create(int type) {
  FxP_Expression *expression = fx_alloc(FxP_Expression);
  verify_memory(expression);

  Array *value = Array_create(4);
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
    array_each(fxp_expression_value(expression), fxp_expression_free);
  }

  fxp_expression_free_husk(expression);
}

void fxp_expression_free_husk(FxP_Expression *expression) {
  array_free(fxp_expression_value(expression));
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

  Array *values = fxp_expression_value(expression);
  int *type = fx_alloc(int);
  *type = token_type;
  array_push(values, type);
  array_push(values, bit);

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
  FxP_Method *call = FxP_Method_create();
  verify_memory(call);

  fxp_method_set_message(call, method_name);
  FxP_Expression *arguments = FxP_Expression_create(FXP_ST_METHOD_ARGUMENTS);
  fxp_list_set(arguments, 0, argument);
  fxp_method_set_arguments(call, arguments);

  return call;
error:
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
  fxp_list_unshift(list, function);

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

FxP_Method *FxP_Method_create_operator(FxP_Expression *receiver, FxP_Literal *message, FxP_Expression *argument) {
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

FxP_List *fxp_list_convert(FxP_Grouped *group) {
  fxp_expression_type(group) = FXP_ST_LIST;
  return group;
}

FxP_List *FxP_List_create_deferred() {
  FxP_Literal *value = FxP_Literal_create(NULL, TOKEN_DEFERRED_ARGUMENT);
  verify(value);

  FxP_List *list = FxP_Expression_create(FXP_ST_LIST);
  verify(list);
  fxp_expression_push(list, value);

  return list;
error:
  if (value) { fxp_expression_free(value); }
  return NULL;
}

FxP_List *FxP_List_create_double(FxP_Expression *first, FxP_Expression *second) {
  FxP_List *list = FxP_Expression_create(FXP_ST_LIST);
  verify(list);

  fxp_expression_push(list, first);
  fxp_expression_push(list, second);

  return list;
error:
  return NULL;
}

// this is pretty inefficient for longer lists since tail is finished first
// would be better to just reverse the index on read and write to end
FxP_List *fxp_list_unshift(FxP_List *list, FxP_Expression *value) {
  int length = fxp_list_length(list);

  // shove last element in again to trigger auto expansion if necessary
  fxp_expression_push(list, fxp_list_get(list, length - 1));

  // move each element to the one behind it
  int i;
  for (i = 1; i <= length; i++) {
    fxp_list_set(list, i, fxp_list_get(list, i - 1));
  }

  // put new value in the front
  fxp_list_set(list, 0, value);

  return list;
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

FxP_Function *FxP_Function_create_no_args(FxP_Expressions *expressions) {
  FxP_Function *function = FxP_Expression_create(FXP_ST_FUNCTION);
  verify(function);

  fxp_function_set_expressions(function, expressions);

  return function;
error:
  return NULL;
}

FxP_Function *FxP_Function_create(FxP_Expressions *expressions, FxP_List *list) {
  FxP_Function *function = FxP_Expression_create(FXP_ST_FUNCTION);
  verify(function);

  fxp_expression_type(list) = FXP_ST_FUNCTION_ARGUMENTS;

  fxp_function_set_expressions(function, expressions);
  fxp_function_set_arguments(function, list);

  return function;
error:
  return NULL;
}

FxP_LocalAssign *FxP_LocalAssign_create(FxP_Lookup *variable, FxP_Expression *value) {
  FxP_Function *local = FxP_Expression_create(FXP_ST_LOCAL_ASSIGN);
  verify(local);

  fxp_local_assignment_set_variable(local, variable);
  fxp_local_assignment_set_value(local, value);

  return local;
error:
  return NULL;
}

FxP_LocalAssign *FxP_ColonExpression_create(FxP_Lookup *variable, FxP_Expression *value) {
  FxP_Function *colon = FxP_Expression_create(FXP_ST_COLON_EXPRESSION);
  verify(colon);

  fxp_colon_expression_set_variable(colon, variable);
  fxp_colon_expression_set_value(colon, value);

  return colon;
error:
  return NULL;
}
