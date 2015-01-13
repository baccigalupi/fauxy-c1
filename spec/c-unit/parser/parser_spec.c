#include "../../../lib/parser/bit.h"
#include "../../../lib/parser/fx_parse.h"
#include "../../../lib/parser/expression_inspect.h"
#include "../../../lib/parser/parse.tab.h"
#include "../../../lib/parser/lex.yy.h"
#include "../lib/spec.h"

char *test_operator_method_call() {
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

char *test_empty_function() {
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

char *all_specs() {
  spec_setup("Parsing Expressions");

  run_spec(test_operator_method_call);

  run_spec(test_empty_function);
  // run_spec(test_empty_function_with_line_end);
  // run_spec(test_function_with_expression);
  // run_spec(test_function_with_multiple_expressions);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
