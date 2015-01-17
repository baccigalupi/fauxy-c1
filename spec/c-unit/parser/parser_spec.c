#include "../../../lib/parser/bit.h"
#include "../../../lib/parser/fx_parse.h"
#include "../../../lib/parser/expression_inspect.h"
#include "../../../lib/parser/parse.tab.h"
#include "../../../lib/parser/lex.yy.h"
#include "../lib/spec.h"

char *test_operator_method_call() {
  spec_describe("opreator expression: 1 + 1");
  FxP_ParserContext *context = parse_string("1 + 1\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_implicit_method_call_with_parens() {
  spec_describe("implicit method: print(1)");
  FxP_ParserContext *context = parse_string("print(1)\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_implicit_method_call_no_parens() {
  spec_describe("implicit method no parens: print 'word'");
  FxP_ParserContext *context = parse_string("print 'word'\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}


char *test_empty_function() {
  spec_describe("empty function: -> {}");
  FxP_ParserContext *context = parse_string("-> {}\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"function_definition\": {\"expressions\": [\n\n]}}\n"
                    "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_empty_function_with_line_end() {
  spec_describe("empty function: -> {\\n}");
  FxP_ParserContext *context = parse_string("-> {\n}\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"function_definition\": {\"expressions\": [\n\n]}}\n"
                    "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_function_with_expression() {
  spec_describe("function one expression: -> { 1 + 1 }");
  FxP_ParserContext *context = parse_string("-> {\n1 + 1\n}\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"function_definition\": {\"expressions\": [\n"
                      "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"
                          "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}\n"
                      "]}}\n"
                      "]}}\n"
                    "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_function_with_multiple_expressions() {
  spec_describe("function two expressions: -> { 1 + 1; print 'word' }");
  FxP_ParserContext *context = parse_string("-> {\n1 + 1\n print 'word'\n}\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                      "{\"function_definition\": {\"expressions\": [\n"
                      "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"
                          "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}\n"
                      "]}},\n"
                      "{\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}, \"method_arguments\": [\n"
                          "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
                      "]}}\n"
                      "]}}\n"
                    "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_expression_function_with_expression_expression() {
  spec_describe("expression function sandwich: 1 + 1; -> { print 'word' }; 2 * 2");
  FxP_ParserContext *context = parse_string("1 + 1\n-> {\n print 'word'\n}\n2 * 2\n");

  String *inspection = fxp_parser_inspect(context);
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
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_parened_method_call() {
  spec_describe("method: Print.line('word') ");
  FxP_ParserContext *context = parse_string("Print.line('word')\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Class Identifier\", \"bit\": {\"STRING\": \"Print\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"line\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_no_parens_method_call() {
  spec_describe("method: Print.line 'word' ");
  FxP_ParserContext *context = parse_string("Print.line 'word' \n");

  String *inspection = fxp_parser_inspect(context);
  char *expected = "{\"expressions\": [\n"
        "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Class Identifier\", \"bit\": {\"STRING\": \"Print\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"line\"}}}, \"method_arguments\": [\n"
            "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"word\"}}}\n"
        "]}}\n"
      "]}";
  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_method_call_with_block() {
  spec_describe("method with block: collection.map -> (e) { Print.line(e) } ");
  FxP_ParserContext *context = parse_string("collection.map -> (e) { Print.line(e) }\n");

  String *inspection = fxp_parser_inspect(context);
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

  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_multi_operator_method() {
  spec_describe("multi operator method chain: 1 + (2 * 3) - 5");
  FxP_ParserContext *context = parse_string("1 + (2 * 3) - 5\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 1}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"+\"}}}, \"method_arguments\": [\n"
                    "{\"method_call\": {\"receiver\": {\"grouped_expression\": [\n"
                    "{\"method_call\": {\"receiver\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 2}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"*\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 3}}}\n"
                    "]}}\n"
                    "]}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"-\"}}}, \"method_arguments\": [\n"
                    "{\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 5}}}\n"
                    "]}}\n"
                    "]}}\n"
                    "]}";

  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *test_function_assignment() {
  spec_describe("multi operator method chain: convert: -> (n: 11) { 'eleven' }");
  FxP_ParserContext *context = parse_string("convert: -> (n: 11) { 'eleven' }\n");

  String *inspection = fxp_parser_inspect(context);
  char *expected =  "{\"expressions\": [\n"
                    "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"convert\"}}}, \"right\": {\"function_definition\": {\"function_arguments\": [\n"
                    "{\"colon_expression\": {\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"n\"}}}, \"right\": {\"literal\": {\"class\": \"Integer\", \"bit\": {\"INTEGER\": 11}}}}}\n"
                    "], \"expressions\": [\n"
                    "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"eleven\"}}}\n"
                    "]}}}}\n"
                    "]}";

  assert_strings_equal(string_value(inspection), expected, "ast");

  fxp_parser_context_free(context);
  string_free(inspection);

  return NULL;
}

char *all_specs() {
  spec_setup("Parsing Expressions");

  run_spec(test_operator_method_call);
  run_spec(test_implicit_method_call_with_parens);
  run_spec(test_implicit_method_call_no_parens);

  run_spec(test_empty_function);
  run_spec(test_empty_function_with_line_end);
  run_spec(test_function_with_expression);
  run_spec(test_function_with_multiple_expressions);

  run_spec(test_expression_function_with_expression_expression);
  run_spec(test_function_with_multiple_expressions);

  run_spec(test_parened_method_call);
  run_spec(test_no_parens_method_call);
  run_spec(test_method_call_with_block);

  run_spec(test_multi_operator_method);
  run_spec(test_function_assignment);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
