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
  spec_describe("empty block: -> {}");
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
  spec_describe("empty block: -> {\\n}");
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
  spec_describe("empty block: -> { 1 + 1 }");
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
  spec_describe("empty block: -> { 1 + 1; print 'word' }");
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

char *all_specs() {
  spec_setup("Parsing Expressions");

  run_spec(test_operator_method_call);
  run_spec(test_implicit_method_call_with_parens);
  run_spec(test_implicit_method_call_no_parens);

  run_spec(test_empty_function);
  run_spec(test_empty_function_with_line_end);
  run_spec(test_function_with_expression);
  run_spec(test_function_with_multiple_expressions);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
