#include "../../../lib/parser/bit.h"
#include "../../../lib/parser/parse.tab.h"
#include "../../../lib/parser/lex.yy.h"
#include "../lib/spec.h"

char *test_empty_function() {
  // parse_string("-> {}");

  return NULL;
}

char *all_specs() {
  spec_setup("Parsing Expressions");

  run_spec(test_empty_function);
  // run_spec(test_empty_function_with_line_end);
  // run_spec(test_function_with_expression);
  // run_spec(test_function_with_multiple_expressions);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
