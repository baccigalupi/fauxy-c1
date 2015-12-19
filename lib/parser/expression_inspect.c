#include "../bricks/string.h"
#include "expression_inspect.h"

// void pointer so that it can be used as an array iterator
void *fxp_inspect(void *element) {
  FxP_Expression *expression = element;
  json_t *root = fxp_inspection_body(expression);
  verify(root);

  json_gen(root);
  return json;
error:
  return NULL;
}

json_t *fxp_inspection_body(FxP_Expression *expression) {
  if (!expression) { return json_string("NULL"); }
  int type = fxp_expression_type(expression);
  char *key = "unknown_expression";
  json_t *body = json_string("huh?");

  json_t *root = json_object();
  verify(root);

  switch(type) {
  case FX_ST_LITERAL:
    key = "literal";
    body = fxp_literal_body(expression);
    break;
  case FX_ST_LOOKUP:
    key = "lookup";
    body = fxp_lookup_body(expression);
    break;
  case FX_ST_METHOD_CALL:
    key = "method_call";
    body =  fxp_method_call_body(expression);
    break;
  case FX_ST_FUNCTION_DEFINITION:
    key = "function_definition";
    body = fxp_function_definition_body(expression);
    break;
  case FX_ST_GROUPED:
    key = "grouped_expression";
    body = fxp_inspection_body(fxp_expression_value_at(expression, 0));
    break;
  case FX_ST_LIST:
    key = "list";
    body = fxp_forward_list_body(expression);
    break;
  case FX_ST_METHOD_CALL_ARGUMENTS:
    key = "method_arguments";
    body = fxp_forward_list_body(expression);
    break;
  case FX_ST_FUNCTION_DEFINITION_ARGUMENTS:
    key = "function_arguments";
    body = fxp_forward_list_body(expression);
    break;
  case FX_ST_COLON_EXPRESSION:
    key = "colon_expression";
    body = fxp_left_right_body(expression);
    break;
  case FX_ST_EXPRESSIONS:
    key = "expressions";
    body = fxp_backwards_list_body(expression);
    break;
  case FX_ST_IMPORT:
    key = "import";
    body = fxp_import_body(expression);
    break;
  }

  verify(body);

  json_object_set_new(root, key, body);
  return root;
error:
  if (root) { json_decref(root); }
  if (body) { json_decref(root); }
  return NULL;
}

json_t *fxp_literal_body(FxP_Literal *expression) {
  /*{"class": "String", "bit": {"STRING": "hello world"}}"*/
  json_t *root = json_object();
  FxB_String *class_value = fxp_literal_class_description(expression);
  json_t *bit_body = NULL;

  verify(root);
  verify(class_value);

  if (fxp_literal_bit(expression)) {
    bit_body = fxp_bit_body_inspect(fxp_literal_bit(expression));
    verify(bit_body);
    json_object_set_new(root, "bit", bit_body);
  } else if (fxp_literal_type(expression) == TOKEN_TRUE) {
    json_object_set_new(root, "value", json_true());
  } else {
    json_object_set_new(root, "value", json_false());
  }

  json_object_set_new(root, "class", json_string(fxb_string_value(class_value)));

  fxb_string_free(class_value);

  return root;
error:
  if (bit_body) { json_decref(bit_body); }
  if (root)     { json_decref(root); }
  if (class_value) { fxb_string_free(class_value); }
  return NULL;
}

json_t *fxp_lookup_body(FxP_Literal *expression) {
  /*{"type": "Identifier", "bit": {"STRING": "hello world"}}"*/
  json_t *bit_body = fxp_bit_body_inspect(fxp_literal_bit(expression));
  json_t *root = json_object();
  FxB_String *type_value = fxp_lookup_type_description(expression);

  verify(bit_body);
  verify(root);
  verify(type_value);

  json_object_set_new(root, "type", json_string(fxb_string_value(type_value)));
  json_object_set_new(root, "bit", bit_body);

  fxb_string_free(type_value);

  return root;
error:
  if (bit_body) { json_decref(bit_body); }
  if (root)     { json_decref(root); }
  if (type_value) { fxb_string_free(type_value); }
  return NULL;
}

json_t *fxp_method_call_body(FxP_Literal *expression) {
  /*{"receiver": inpection, "message": inspection, "arguments": inspection}*/
  json_t *root = json_object();
  json_t *body = NULL;
  FxP_Expression *part = NULL;

  verify(root);

  part = fxp_method_call_receiver(expression);
  if (part) {
    body = fxp_inspection_body(part);
    verify(body);
    json_object_set_new(root, "receiver", body);
  }

  json_object_set_new(root, "message", fxp_inspection_body(fxp_method_call_message(expression)));

  part = NULL;
  part = fxp_method_call_arguments(expression);
  if (part) {
    body = fxp_forward_list_body(part);
    verify(body);
    json_object_set_new(root, "arguments", body);
  }

  return root;
error:
  if (body) { json_decref(body); }
  if (root) { json_decref(root); }
  return NULL;
}

json_t *fxp_function_definition_body(FxP_Literal *expression) {
  /*{"arguments": inpection, "expressions": inspection}*/
  json_t *root = json_object();
  json_t *body = NULL;
  FxP_Expression *part = NULL;

  verify(root);

  part = fxp_function_definition_arguments(expression);
  if (part) {
    body = fxp_inspection_body(part);
    verify(body);
    json_object_set_new(root, "arguments", body);
  }

  body = fxp_backwards_list_body(fxp_function_definition_expressions(expression));
  verify(body);
  json_object_set_new(root, "expressions", body);

  return root;
error:
  if (body) { json_decref(body); }
  if (root) { json_decref(root); }
  return NULL;
}

json_t *fxp_backwards_list_body(FxP_Expression *expression) {
  json_t *root = json_array();
  json_t *list_json = NULL;
  FxP_Expression *list_exp = NULL;
  verify(root);

  int i;
  for (i = fxb_array_length(fxp_expression_value(expression)) - 1; i >= 0; i--) {
    list_exp = fxp_list_get(expression, i);
    list_json = fxp_inspection_body(list_exp);
    verify(list_json);
    json_array_append_new(root, list_json);
  }

  return root;
error:
  if (root) { json_decref(root); }
  if (list_json) { json_decref(list_json); }
  return NULL;
}

json_t *fxp_forward_list_body(FxP_Expression *expression) {
  json_t *root = json_array();
  json_t *list_json = NULL;
  FxP_Expression *list_exp = NULL;
  verify(root);

  int i;
  int length = fxb_array_length(fxp_expression_value(expression));
  for (i = 0; i < length; i++) {
    list_exp = fxp_list_get(expression, i);
    list_json = fxp_inspection_body(list_exp);
    verify(list_json);
    json_array_append_new(root, list_json);
  }

  return root;
error:
  if (root) { json_decref(root); }
  if (list_json) { json_decref(list_json); }
  return NULL;
}

json_t *fxp_left_right_body(FxP_Expression *expression) {
  /*{"left": inpection, "right": inspection}*/
  json_t *root = json_object();
  json_t *body = NULL;

  verify(root);

  body = fxp_inspection_body(fxp_expression_left(expression));
  verify(body);
  json_object_set_new(root, "left", body);

  body = fxp_inspection_body(fxp_expression_right(expression));
  verify(body);
  json_object_set_new(root, "right", body);

  return root;
error:
  if (body) { json_decref(body); }
  if (root) { json_decref(root); }
  return NULL;
}


json_t *fxp_import_body(FxP_Expression *expression) {
  /*{"path": inpection}*/
  json_t *root = json_object();
  json_t *body = NULL;

  verify(root);

  body = fxp_inspection_body(fxp_import_path_expression(expression));
  verify(body);
  json_object_set_new(root, "path", body);

  return root;
error:
  if (body) { json_decref(body); }
  if (root) { json_decref(root); }
  return NULL;
}

// TODO: inline to avoid releasing String objects
FxB_String *fxp_literal_class_description(FxP_Literal *literal) {
  FxB_String *description;

  if (fxp_literal_type(literal) == TOKEN_STRING) {
    description = FxB_String_create("String");
  } else if (fxp_literal_type(literal) == TOKEN_EVAL_STRING) {
    description = FxB_String_create("EvalString");
  } else if (fxp_literal_type(literal) == TOKEN_REGEX) {
    description = FxB_String_create("Regex");
  } else if (fxp_literal_type(literal) == TOKEN_INTEGER) {
    description = FxB_String_create("Integer");
  } else if (fxp_literal_type(literal) == TOKEN_FLOAT) {
    description = FxB_String_create("Float");
  } else if (fxp_literal_type(literal) == TOKEN_TRUE) {
    description = FxB_String_create("Boolean");
  } else if (fxp_literal_type(literal) == TOKEN_FALSE) {
    description = FxB_String_create("Boolean");
  } else {
    description = FxB_String_create_blank();
  }

  verify(description);

  return description;
error:
  return NULL;
}

// TODO: inline to avoid alloc and release of strings
FxB_String *fxp_lookup_type_description(FxP_Lookup *lookup) {
  FxB_String *description;

  if (fxp_lookup_type(lookup) == TOKEN_ID) {
    description = FxB_String_create("Identifier");
  } else {
    description = FxB_String_create("Class Identifier");
  }

  verify(description);

  return description;
error:
  return NULL;
}
