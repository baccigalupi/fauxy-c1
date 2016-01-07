#include "../../../lib/parser/_parser.h"
#include "../../../lib/parser/parse.tab.h"
#include "../../../lib/parser/lex.yy.h"
#include "../lib/spec.h"

#define setup_json()    char *inspection = fxp_parser_inspect(context);                               \
                        json_error_t error;                                                           \
                        json_t *root = json_loads(inspection, 0, &error);                             \
                        json_t *expressions = json_object_get(root, "expressions");                   \
                        json_t *expression = json_array_get(expressions, 0);                          \
                                                                                                      \
                        json_t *element;

#define cleanup()       fxp_parser_context_free(context); \
                        free(inspection);                 \
                        json_decref(root);

char *test_operator_method_call() {
  spec_describe("opreator expression: 1 + 1");
  FxP_ParserContext *context = parse_string("1 + 1\n");

  setup_json();

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "receiver"),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "receiver correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "+", "message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(expression, "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "arguments correct");

  cleanup();

  return NULL;
}

char *test_implicit_method_call_with_parens() {
  spec_describe("implicit method: print(1)");
  FxP_ParserContext *context = parse_string("print(1)\n");
  setup_json();

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "print", "message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(expression, "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "arguments correct");

  cleanup();
  return NULL;
}

char *test_implicit_method_call_no_parens() {
  spec_describe("implicit method no parens: print 'word'");
  FxP_ParserContext *context = parse_string("print 'word'\n");
  setup_json();

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "print", "message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(expression, "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "word", "arguments correct");

  cleanup();
  return NULL;
}

char *test_two_expressions() {
  spec_describe("test order of two expressions: 1 + 1\nprint 'word'");
  FxP_ParserContext *context = parse_string("1 + 1\nprint 'word'");

  setup_json();

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "receiver"),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "first expression receiver correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "+", "second expression message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(expression, "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "second expression arguments correct");

  expression = json_array_get(expressions, 1);                          \

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(expression, "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "print", "first expression message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(expression, "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "word", "first expression arguments correct");

  cleanup();

  return NULL;
}


char *test_empty_function() {
  spec_describe("empty function: -> {}");
  FxP_ParserContext *context = parse_string("-> {}\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\n"
    "  \"expressions\": [\n"
    "    {\n"
    "      \"function_definition\": {\n"
    "        \"expressions\": []\n"
    "      }\n"
    "    }\n"
    "  ]\n"
    "}";
  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_empty_function_with_line_end() {
  spec_describe("empty function: -> {\n}");
  FxP_ParserContext *context = parse_string("-> {\n}\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\n"
    "  \"expressions\": [\n"
    "    {\n"
    "      \"function_definition\": {\n"
    "        \"expressions\": []\n"
    "      }\n"
    "    }\n"
    "  ]\n"
    "}";
  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_function_with_expression() {
  spec_describe("function one expression: -> {\n1 + 1\n}");
  FxP_ParserContext *context = parse_string("-> {\n1 + 1\n}\n");
  setup_json();

  element = json_object_get(
               json_object_get(expression, "function_definition"),
            "expressions");
  assert_ints_equal(json_array_size(element), 1, "expressions size correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(
              json_array_get(
                json_object_get(
                  json_object_get(expression, "function_definition"),
                "expressions"),
              0),
            "method_call"),
          "receiver"),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "first expression receiver correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(
              json_array_get(
                json_object_get(
                  json_object_get(expression, "function_definition"),
                "expressions"),
              0),
            "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "+", "first expression message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(
                json_array_get(
                  json_object_get(
                    json_object_get(expression, "function_definition"),
                  "expressions"),
                0),
              "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "first expression arguments correct");

  cleanup();
  return NULL;
}

char *test_function_with_two_expressions() {
  // TODO: parser can't handle no terminating \n at end of expressions set
  /*spec_describe("function two expressions: -> {\n  1 + 1\n  print 'word'}");*/
  spec_describe("function two expressions: -> {\n  1 + 1\n  print 'word'\n}\n");
  FxP_ParserContext *context = parse_string("-> {\n  1 + 1\n  print 'word'\n}\n");

  setup_json();

  element = json_object_get(
               json_object_get(expression, "function_definition"),
            "expressions");
  assert_ints_equal(json_array_size(element), 2, "expressions size correct");

  expression = json_object_get(
    json_object_get(expression, "function_definition"),
  "expressions");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(
              json_array_get(
                expression,
              0),
            "method_call"),
          "receiver"),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "first expression receiver correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_object_get(
            json_object_get(
              json_array_get(
                expression,
              0),
            "method_call"),
          "message"),
        "lookup"),
      "bit"),
    "STRING");
  assert_strings_equal(json_string_value(element), "+", "first expression message correct");

  element = json_object_get(
      json_object_get(
        json_object_get(
          json_array_get(
            json_object_get(
              json_object_get(
                json_array_get(
                  expression,
                0),
              "method_call"),
            "arguments"),
          0),
        "literal"),
      "bit"),
    "INTEGER");
  assert_ints_equal(json_integer_value(element), 1, "first expression arguments correct");

  /*char *expected =  "{\"expressions\": [\n"*/
                      /*"{\"function_definition\": {\"expressions\": [\n"*/
                      /*"{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"*/
                          /*"{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}\n"*/
                      /*"]}},\n"*/
                      /*"{\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}, \"method_arguments\": [\n"*/
                          /*"{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"*/
                      /*"]}}\n"*/
                      /*"]}}\n"*/
                    /*"]}";*/

  cleanup();
  return NULL;
}

char *test_expression_function_with_expression_expression() {
  spec_describe("expression function sandwich: 1 + 1\n-> {\n print 'word'\n}\n2 * 2");
  FxP_ParserContext *context = parse_string("1 + 1\n-> {\n print 'word'\n}\n2 * 2\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"
                          "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}\n"
                      "]}},\n"
                      "{\"function_definition\": {\"expressions\": [\n"
                      "{\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}, \"method_arguments\": [\n"
                          "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
                      "]}}\n"
                      "]}},\n"
                      "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 2}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"*\"}}}, \"method_arguments\": [\n"
                          "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 2}}}\n"
                      "]}}\n"
                    "]}";
  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_parened_method_call() {
  spec_describe("method: Print.line('word') ");
  FxP_ParserContext *context = parse_string("Print.line('word')\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Class Identifier\", \"bit\": {\"STRING\": \"Print\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"line\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_no_parens_method_call() {
  spec_describe("method: Print.line 'word' ");
  FxP_ParserContext *context = parse_string("Print.line 'word' \n");

  char *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Class Identifier\", \"bit\": {\"STRING\": \"Print\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"line\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_method_call_with_block() {
  spec_describe("method with block: collection.map -> (e) { Print.line(e) } ");
  FxP_ParserContext *context = parse_string("collection.map -> (e) { Print.line(e) }\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"collection\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"map\"}}}, \"method_arguments\": [\n"
                    "{\"function_definition\": {\"function_arguments\": [\n"
                    "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"e\"}}}\n"
                    "], \"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Class Identifier\", \"bit\": {\"STRING\": \"Print\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"line\"}}}, \"method_arguments\": [\n"
                    "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"e\"}}}\n"
                    "]}}\n"
                    "]}}\n"
                    "]}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_multi_operator_method() {
  spec_describe("multi operator method chain: 1 + (n * 3) - 5");
  FxP_ParserContext *context = parse_string("1 + (n * 3) - 5\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"
                    "{\"method_call\": {\"receiver\": {\"grouped_expression\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"*\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 3}}}\n"
                    "]}}\n"
                    "]}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"-\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 5}}}\n"
                    "]}}\n"
                    "]}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_function_assignment() {
  spec_describe("attr assignment with function def: convert: -> (n: 11) { 'eleven' }");
  FxP_ParserContext *context = parse_string("convert: -> (n: 11) { 'eleven' }\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"convert\"}}}, \"right\": {\"function_definition\": {\"function_arguments\": [\n"
                    "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"right\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 11}}}}}\n"
                    "], \"expressions\": [\n"
                    "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"eleven\"}}}\n"
                    "]}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}


char *test_grouped_expression_method_call() {
  spec_describe("grouped expression as receiver: (n / 10).truncate");
  FxP_ParserContext *context = parse_string("(n / 10).truncate\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"grouped_expression\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"/\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 10}}}\n"
                    "]}}\n"
                    "]}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"truncate\"}}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_multi_line_group() {
  spec_describe("multiline group: (\n\tn / 10\n).truncate");
  FxP_ParserContext *context = parse_string("(\n\tn / 10\n).truncate\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"grouped_expression\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"/\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 10}}}\n"
                    "]}}\n"
                    "]}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"truncate\"}}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_multi_line_method_call() {
  spec_describe("multiline method call:  (n / 10)\n\t.truncate");
  FxP_ParserContext *context = parse_string("(n / 10)\n\t.truncate\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"grouped_expression\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"/\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 10}}}\n"
                    "]}}\n"
                    "]}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"truncate\"}}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  spec_describe("multiline method call:  (n / 10).\n\ttruncate");
  context = parse_string("(n / 10).\n\ntruncate\n");

  inspection = fxp_parser_inspect(context);
  expected =        "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"grouped_expression\": [\n"
                    "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"/\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 10}}}\n"
                    "]}}\n"
                    "]}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"truncate\"}}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_multi_line_list() {
  spec_describe("multiline group: (\n\t1,\n\t2, \n\t3\n)");
  FxP_ParserContext *context = parse_string("(\n\t1,\n\t2, \n\t3\n)\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"list\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}},\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 2}}},\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 3}}}\n"
                    "]}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_native_assignment() {
  spec_describe("native assignments: to_s: native('fxi_native_to_s')");
  FxP_ParserContext *context = parse_string("to_s: native('fxi_native_to_s')\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"to_s\"}}}, \"right\": {\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"native\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"fxi_native_to_s\"}}}\n"
                    "]}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_block_assignment() {
  spec_describe("function assignments: ?: -> { !empty? }");
  FxP_ParserContext *context = parse_string("?: -> { !empty? }\n");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"?\"}}}, \"right\": {\"function_definition\": {\"expressions\": [\n"
                        "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"empty?\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"!\"}}}}}\n"
                      "]}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_import_expression() {
  spec_describe("import expression: import 'my-file'");

  FxP_ParserContext *context = parse_string("import 'my-file'");

  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"import\": {\"path\": {\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"my-file\"}}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *test_parse_from_file() {
  spec_describe("parsing content of file, should work the same");

  FxP_ParserContext *context = parse_file("spec/c-unit/interpreter/fixtures/import-test.fx");
  char *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"it-worked?\"}}}, \"right\": {\"literal\": {\"class\": \"Boolean\", \"value\": true}}}}\n"
                    "]}";

  assert_strings_equal(inspection, expected, "ast");

  fxp_parser_context_free(context);
  free(inspection);

  return NULL;
}

char *all_specs() {
  spec_setup("Parsing Expressions");

  run_spec(test_operator_method_call);
  run_spec(test_implicit_method_call_with_parens);
  run_spec(test_implicit_method_call_no_parens);

  run_spec(test_two_expressions);

  run_spec(test_empty_function);
  run_spec(test_empty_function_with_line_end);
  run_spec(test_function_with_expression);
  run_spec(test_function_with_two_expressions);

  /*run_spec(test_expression_function_with_expression_expression);*/
  /*run_spec(test_function_with_multiple_expressions);*/

  /*run_spec(test_parened_method_call);*/
  /*run_spec(test_no_parens_method_call);*/
  /*run_spec(test_method_call_with_block);*/

  /*run_spec(test_multi_operator_method);*/
  /*run_spec(test_function_assignment);*/
  /*run_spec(test_grouped_expression_method_call);*/

  /*run_spec(test_multi_line_group);*/
  /*run_spec(test_multi_line_method_call);*/
  /*run_spec(test_multi_line_list);*/

  /*run_spec(test_native_assignment);*/
  /*run_spec(test_block_assignment);*/

  /*run_spec(test_import_expression);*/

  /*run_spec(test_parse_from_file);*/

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
