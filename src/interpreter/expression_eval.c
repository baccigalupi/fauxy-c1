#include "expression_eval.h"
#include "expression_key.h"
#include "literal.h"
#include "method_call_arguments.h"
#include "../parser/_parser.h"

#define DEBUG_INTERPRETER false

FxI_Object *fxi_evaluate(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  int type = fxp_expression_type(expression);
  FxI_Object *result = NULL;

  if (DEBUG_INTERPRETER) {
    printf("current context has %d attributes\n", fxi_object_attributes_length(fxi_current_context(interpreter)));
    printf("evaluating: %d %s\n", type, fxb_string_value((FxB_String *)fxp_inspect(expression)));
  }

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
  } else if ( type == FX_ST_COLON_EXPRESSION ) {
    result = fxi_evaluate_attr_assign(interpreter, expression);
  } else if ( type == FX_ST_EXPRESSIONS ) {
    result = fxi_evaluate_expressions(interpreter, expression);
  } else if ( type == FX_ST_IMPORT ) {
    result = fxi_evaluate_import(interpreter, expression);
  } else if ( type == FX_ST_NATIVE ) {
    result = fxi_evaluate_native(interpreter, expression);
  } else {
    printf("%d expression evaluation not defined\n", type);
  }

  verify(result);

  return result;
error:
  printf("Evalutaion error: %s\n", fxb_string_value((FxB_String *)fxp_inspect(expression)));
  return NULL;
}

FxI_Object *fxi_evaluate_literal(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  char *key = fxi_literal_key(expression);
  FxI_Object *object;

  if (key) {
    object = fxi_literal_get(interpreter, key);
    if (!object) {
      object = FxI_Object_create(interpreter, NULL); // todo: add class context
      verify(object);
      fxi_object__value(object) = expression;
      fxi_literal_set(interpreter, key, object);
    }
  } else { // floats don't get stored in the literals, so just make one
    object = FxI_Object_create(interpreter, NULL); // todo: add class context
    verify(object);
    fxi_object__value(object) = expression;
  }

  return object;
error:
  return NULL;
}

FxI_Object *fxi_evaluate_attr_assign(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  FxP_Expression *value_expression = fxp_expression_right(expression);
  FxI_Object *result = fxi_evaluate(interpreter, value_expression);
  verify(result);
  char *key = fxi_lookup_key(fxp_expression_left(expression));
  fxi_context_set(interpreter, key, result);
  return result;
error:
  return NULL;
}

FxI_Object *fxi_evaluate_lookup(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  char *key = fxi_lookup_key(expression);
  return fxi_lookup(interpreter, key);
  // TODO: raise evaluation error if not found
}

FxI_Object *fxi_evaluate_method_call_arguments(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  FxI_Object *result = FxI_MethodCallArguments_create(interpreter, expression);
  // TODO: validate arguments?
  return result;
}

// does this happen/make sense?
FxI_Object *fxi_evaluate_function_definition_arguments(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxI_Object *fxi_evaluate_function_definition(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  // TODO: this is the same as creating a literal without a key, wrap it up!
  FxI_Object *object = FxI_Object_create(interpreter, NULL); // todo: add class context
  verify(object);
  fxi_object__value(object) = expression;

  return object;
error:
  return NULL;
}

FxI_Object *fxi_evaluate_method(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxI_Object *fxi_evaluate_grouped(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxI_Object *fxi_evaluate_list(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  return NULL;
}

FxI_Object *fxi_evaluate_colon_expression(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  // need some disambiguation?
  return fxi_evaluate_assignment(interpreter, expression);
}

FxI_Object *fxi_evaluate_assignment(FxI_Interpreter *interpreter, FxP_Expression *expression) {
  FxP_Lookup *left =      fxp_expression_left(expression);
  FxP_Expression *right = fxp_expression_right(expression);

  FxI_Object *value = fxi_evaluate(interpreter, right);
  verify(value)

  printf("lookup key for assignement: %s\n", fxp_lookup_key(left));
  fxi_object_set(fxi_current_context(interpreter), fxp_lookup_key(left), value);
  return value;
error:
  return NULL;
}

FxI_Object *fxi_evaluate_expressions(FxI_Interpreter *interpreter, FxP_Expression *expressions) {
  FxP_Expression *expression = NULL;
  FxI_Object *object = NULL_OBJECT;
  int i;
  for (i = 0; i < fxp_expression_length(expressions); i++) {
    expression = fxp_expression_value_at(expressions, i);
    object = fxi_evaluate(interpreter, expression);
  }
  return object;
}

FxI_Object *fxi_evaluate_import(FxI_Interpreter *interpreter, FxP_ImportExpression *expression) {
  FxP_ParserContext *context = NULL;
  FxP_Expression *path_expression = fxp_import_path_expression(expression);

  // TODO: allow other expressions and verify result is a string
  verify(fxp_is_string_literal(path_expression));

  context = parse_file(fxp_literal_string_value(path_expression));
  verify(context);

  FxI_Object *object = fxi_evaluate_parser(interpreter, context);
  // TODO: free the parser
  return object;
error:
  printf("%d %d\n", fxp_expression_type(path_expression), FX_ST_LITERAL);
  puts("Runtime Error: File path expression is not a string.");
  return NULL;
}

FxI_Object *fxi_evaluate_native(FxI_Interpreter *interpreter, FxP_ImportExpression *expression) {
  FxI_Object *object = FxI_Object_create(interpreter, NULL); // todo: add class for Function
  // TODO: if it is an eval string, need to eval it :(
  // or if evaluable to a string need to do both
  FxP_Expression *path = fxp_native_function_name(expression);
  verify(fxp_is_string_literal(path));
  char *function_name = fxp_literal_string_value(path);

  FxB_HashMap *registry = fxi_interpreter_registry(interpreter);
  FxI_NativeFunction *native_function = fxb_hash_map_get(registry, function_name);
  fxi_object__value(object) = native_function;

  return object;
error:
  return NULL;
}

FxI_Object *fxi_evaluate_parser(FxI_Interpreter *interpreter, FxP_ParserContext *context) {
  FxB_List *list = fxp_parser_context_list(context);
  FxB_Node *node = NULL;
  FxP_Expressions *expressions = NULL;
  FxI_Object *object = NULL_OBJECT;

  for (node = fxb_list_node_first(list); node != NULL; node = fxb_node_next(node)) {
    expressions = fxb_node_value(node);
    object = fxi_evaluate(interpreter, expressions);
  }

  return object;
}
