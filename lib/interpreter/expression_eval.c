#include "expression_eval.h"
#include "expression_key.h"
#include "literal.h"
#include "pool.h"
#include "method_call_arguments.h"
#include "../parser/_parser.h"

FxN_Object *fxi_evaluate(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  int type = fxp_expression_type(expression);
  FxN_Object *result = NULL;

  if (type == FX_ST_LITERAL) {
    result = fxi_evaluate_literal(interpreter, expression);
  } else if ( type == FX_ST_LOOKUP ) {
    result = fxi_evaluate_lookup(interpreter, expression);
  } else if ( type == FX_ST_METHOD_CALL ) {
    result = fxi_evaluate_method(interpreter, expression);
  } else if ( type == FX_ST_FUNCTION_DEFINITION ) {
    result = fxi_evaluate_function_definition(interpreter, expression);
  } else if ( type == FX_ST_GROUPED) {
    result = fxi_evaluate_grouped(interpreter, expression);
  } else if (type == FX_ST_LIST ) {
    result = fxi_evaluate_list(interpreter, expression);
  } else if ( type == FX_ST_METHOD_CALL_ARGUMENTS ) {
    result = fxi_evaluate_method_call_arguments(interpreter, expression);
  } else if ( type == FX_ST_FUNCTION_DEFINITION_ARGUMENTS ) {
    result = fxi_evaluate_function_definition_arguments(interpreter, expression);
  } else if ( type == FX_ST_LOCAL_ASSIGN ) {
    result = fxi_evaluate_local_assign(interpreter, expression);
  } else if ( type == FX_ST_COLON_EXPRESSION ) {
    result = fxi_evaluate_attr_assign(interpreter, expression);
  } else if ( type == FX_ST_EXPRESSIONS ) {
    result = fxi_evaluate_expressions(interpreter, expression);
  } else if ( type == FX_ST_IMPORT ) {
    result = fxi_evaluate_import(interpreter, expression);
  } else {
    printf("%d expression evaluation not defined\n", type);
  }

  verify(result);

  return result;
error:
  return NULL;
}

FxN_Object *fxi_evaluate_literal(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  char *key = fxi_literal_key(expression);
  FxN_Object *object;

  if (key) {
    object = fxi_literal_get(interpreter, key);
    if (!object) {
      object = FxN_Object_create(interpreter, NULL); // todo: add class context
      verify(object);
      fxn_object__value(object) = expression;
      fxi_literal_set(interpreter, key, object);
    }
  } else { // floats don't get stored in the literal pool, so just make one
    object = FxN_Object_create(interpreter, NULL); // todo: add class context
    verify(object);
    fxn_object__value(object) = expression;
  }

  return object;
error:
  return NULL;
}

FxN_Object *fxi_evaluate_attr_assign(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  FxP_Expression *value_expression = fxp_expression_right(expression);
  FxN_Object *result = fxi_evaluate(interpreter, value_expression);
  char *key = fxi_lookup_key(fxp_expression_left(expression));
  fxi_context_set(interpreter, key, result);
  return result;
}

FxN_Object *fxi_evaluate_lookup(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  char *key = fxi_lookup_key(expression);
  return fxi_lookup(interpreter, key);
  // TODO: raise evaluation error if not found
}

FxN_Object *fxi_evaluate_method_call_arguments(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  FxN_Object *result = FxN_MethodCallArguments_create(interpreter, expression);
  // TODO: validate arguments?
  return result;
}

// does this happen/make sense?
FxN_Object *fxi_evaluate_function_definition_arguments(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxN_Object *fxi_evaluate_function_definition(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  // TODO: this is the same as creating a literal without a key, wrap it up!
  FxN_Object *object = FxN_Object_create(interpreter, NULL); // todo: add class context
  verify(object);
  fxn_object__value(object) = expression;

  return object;
error:
  return NULL;
}

FxN_Object *fxi_evaluate_method(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxN_Object *fxi_evaluate_grouped(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxN_Object *fxi_evaluate_list(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxN_Object *fxi_evaluate_local_assign(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

/*FxN_Object *fxi_evaluate_colon_expression(FxI_Interpreter *interpreter, FxP_Expression *expression) {*/
  /*return NULL;*/
/*}*/

FxN_Object *fxi_evaluate_expressions(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxN_Object *fxi_evaluate_import(FxI_Interpreter *interpreter, FxP_ImportExpression *expression) {
  FxP_ParserContext *context = NULL;
  FxP_Expression *path_expression = fxp_import_path_expression(expression);

  if (fxp_expression_type(path_expression) == FX_ST_LITERAL && fxp_literal_bit_type(path_expression) == FX_BIT_STRING) {
    context = parse_file(fxp_bit_string_value(fxp_literal_bit(path_expression)));
    verify(context);
    printf("%s\n", fxp_inspect(context));
    /*return fxi_evaluate(interpreter, fxp_parser_current_context(context));*/
  /* TODO: else if case around expression that resolves to string */
  } else {
    printf("%d %d\n", fxp_expression_type(path_expression), FX_ST_LITERAL);
    puts("Runtime Error: File path expression is not a string.");
    return NULL;
  }
error:
  return NULL;
}
