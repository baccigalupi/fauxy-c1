#include "../../../lib/bricks/string.h"

#include "../lib/spec.h"

char *test_create_from_literal() {
  spec_describe("Create from string literal");
  FxB_String *string = FxB_String_create("0123456789");

  assert_ints_equal(fxb_string_length(string), 10, "length");
  assert_ints_equal(fxb_string_capacity(string), 32, "capacity");
  assert_strings_equal(fxb_string_value(string), "0123456789", "value");

  fxb_string_free(string);

  return NULL;
}

char *test_create_from_allocated() {
  spec_describe("Create from allocated string");
  CHAR *str = calloc(4, sizeof(CHAR));
  STRCPY(str, "foo");

  FxB_String *string = FxB_String_create(str);

  fx_pfree(str);

  assert_ints_equal(fxb_string_length(string), 3, "length");
  assert_ints_equal(fxb_string_capacity(string), 8, "capacity");
  assert_strings_equal(fxb_string_value(string), "foo", "value");

  fxb_string_free(string);

  return NULL;
}

char *test_accessing_by_index() {
  spec_describe("Accessing string characters by index");

  FxB_String *string = FxB_String_create("0123456789");

  assert_equal(fxb_string_char_at(string, 0), '0', "0 index");
  assert_equal(fxb_string_char_at(string, 1), '1', "1 index");
  assert_equal(fxb_string_char_at(string, 9), '9', "9 index");

  assert_equal(fxb_string_char_at(string, 105), '\0', "null for out of range");

  fxb_string_free(string);

  return NULL;
}

char *test_push_character() {
  spec_describe("Pushing individual characters to a string");

  FxB_String *string = FxB_String_create("foo");

  assert_ints_equal(fxb_string_capacity(string), 8, "capacity");
  assert_ints_equal(fxb_string_offset(string), 6, "offset"); // 16 real capacity - 3 length = 13, divide by 2, floor = 6

  fxb_string_push_char(string, '.');
  assert_equal(fxb_string_length(string), 4, "first push: string length");
  assert_strings_equal(fxb_string_value(string), "foo.", "string value");

  fxb_string_push_char(string, 'b');
  assert_equal(fxb_string_length(string), 5, "second push: string length");
  assert_strings_equal(fxb_string_value(string), "foo.b", "string value");

  fxb_string_push_char(string, 'a');
  assert_equal(fxb_string_length(string), 6, "third push: string length");
  assert_strings_equal(fxb_string_value(string), "foo.ba", "string value");

  fxb_string_push_char(string, 'r');
  assert_equal(fxb_string_length(string), 7, "fourth push: string length");
  assert_strings_equal(fxb_string_value(string), "foo.bar", "string value");

  fxb_string_push_char(string, '(');
  assert_equal(fxb_string_length(string), 8, "fifth push: string length");
  assert_strings_equal(fxb_string_value(string), "foo.bar(", "string value");
  assert_ints_equal(fxb_string_capacity(string), 8, "capacity");

  fxb_string_push_char(string, ')');
  assert_ints_equal(fxb_string_capacity(string), 32, "fifth push: capacity");
  assert_ints_equal(fxb_string_offset(string), 28, "offset"); // 64 real capacity - 8 length = 56, divide 2 = 28
  assert_equal(fxb_string_length(string), 9, "string length");
  assert_strings_equal(fxb_string_value(string), "foo.bar()", "string value");

  fxb_string_free(string);

  return NULL;
}

char *test_concat() {
  spec_describe("Pushing char arrays into to a string");

  FxB_String *string = FxB_String_create("foo");

  assert_ints_equal(fxb_string_capacity(string), 8, "capacity");

  fxb_string_add_chars(string, ".bar()");

  assert_equal(fxb_string_length(string), 9, "fifth push: string length");
  assert_strings_equal(fxb_string_value(string), "foo.bar()", "string value");
  assert_ints_equal(fxb_string_capacity(string), 32, "capacity");

  fxb_string_free(string);

  return NULL;
}

char *test_create_blank() {
  spec_describe("Creating an empty string, for use as a null pattern string");

  FxB_String *string = FxB_String_create_blank();

  assert_ints_equal(fxb_string_length(string), 0, "length");
  assert_ints_equal(fxb_string_capacity(string), 0, "capacity");

  fxb_string_free(string);

  return NULL;
}

char *test_duplication() {
  spec_describe("Duplicating string");

  FxB_String *string = FxB_String_create("Hello");
  FxB_String *duplicate = fxb_string_duplicate(string);

  assert_strings_equal(fxb_string_value(string), fxb_string_value(duplicate), "same value");
  assert_not_equal(string, duplicate, "different addresses");

  fxb_string_free(string);
  fxb_string_free(duplicate);

  return NULL;
}

char *test_unshift_character() {
  spec_describe("Unshifting individual characters to a string");

  FxB_String *string = FxB_String_create("foo");

  assert_ints_equal(fxb_string_capacity(string), 8, "capacity");
  assert_ints_equal(fxb_string_offset(string), 6, "offset"); // 16 real capacity - 3 length = 13, divide by 2, floor = 6

  fxb_string_unshift_char(string, '.');
  assert_equal(fxb_string_length(string), 4, "first push: string length");
  assert_strings_equal(fxb_string_value(string), ".foo", "string value");

  fxb_string_unshift_char(string, 'r');
  assert_equal(fxb_string_length(string), 5, "second push: string length");
  assert_strings_equal(fxb_string_value(string), "r.foo", "string value");

  fxb_string_unshift_char(string, 'a');
  assert_equal(fxb_string_length(string), 6, "third push: string length");
  assert_strings_equal(fxb_string_value(string), "ar.foo", "string value");

  fxb_string_unshift_char(string, 'b');
  assert_equal(fxb_string_length(string), 7, "fourth push: string length");
  assert_strings_equal(fxb_string_value(string), "bar.foo", "string value");

  fxb_string_unshift_char(string, '-');
  assert_equal(fxb_string_length(string), 8, "fifth push: string length");
  assert_strings_equal(fxb_string_value(string), "-bar.foo", "string value");

  fxb_string_unshift_char(string, 'x');
  assert_ints_equal(fxb_string_length(string), 9, "fifth push: string length");
  assert_strings_equal(fxb_string_value(string), "x-bar.foo", "string value");

  fxb_string_unshift_char(string, 'f');
  assert_ints_equal(fxb_string_capacity(string), 32, "fifth push: capacity");
  assert_ints_equal(fxb_string_offset(string), 26, "offset");
  assert_equal(fxb_string_length(string), 10, "string length");
  assert_strings_equal(fxb_string_value(string), "fx-bar.foo", "string value");

  fxb_string_free(string);

  return NULL;
}

char *test_wrap() {
  FxB_String *string = FxB_String_create("\"foo\": \"bar\"");

  fxb_string_wrap(string, '{', '}');

  assert_strings_equal(fxb_string_value(string), "{\"foo\": \"bar\"}", "string value");

  fxb_string_free(string);
  return NULL;
}

char *all_specs() {
  spec_setup("Brick FxB_String");

  run_spec(test_create_from_literal);
  run_spec(test_create_from_allocated);
  run_spec(test_accessing_by_index);
  run_spec(test_push_character);
  run_spec(test_unshift_character);
  run_spec(test_concat);

  run_spec(test_create_blank);
  run_spec(test_duplication);

  run_spec(test_wrap);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
