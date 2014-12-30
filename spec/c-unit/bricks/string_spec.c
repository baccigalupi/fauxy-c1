#include "../../../lib/bricks/string.h"

#include "../lib/spec.h"

char *test_create_from_literal() {
  spec_describe("Create from string literal");
  String *string = String_create("0123456789");

  assert_ints_equal(string_length(string), 10, "length");
  assert_ints_equal(string_capacity(string), 32, "capacity");
  assert_strings_equal(string_value(string), "0123456789", "value");

  string_free(string);

  return NULL;
}

char *test_create_from_allocated() {
  spec_describe("Create from allocated string");
  CHAR *str = calloc(4, sizeof(CHAR));
  STRCPY(str, "foo");

  String *string = String_create(str);

  fx_pfree(str);

  assert_ints_equal(string_length(string), 3, "length");
  assert_ints_equal(string_capacity(string), 8, "capacity");
  assert_strings_equal(string_value(string), "foo", "value");

  string_free(string);

  return NULL;
}

char *test_accessing_by_index() {
  spec_describe("Accessing string characters by index");

  String *string = String_create("0123456789");

  assert_equal(string_char_at(string, 0), '0', "0 index");
  assert_equal(string_char_at(string, 1), '1', "1 index");
  assert_equal(string_char_at(string, 9), '9', "9 index");

  assert_equal(string_char_at(string, 105), '\0', "null for out of range");

  string_free(string);

  return NULL;
}

char *test_push_character() {
  spec_describe("Pushing individual characters to a string");

  String *string = String_create("foo");

  assert_ints_equal(string_capacity(string), 8, "capacity");
  assert_ints_equal(string_offset(string), 6, "offset"); // 16 real capacity - 3 length = 13, divide by 2, floor = 6

  string_push_char(string, '.');
  assert_equal(string_length(string), 4, "first push: string length");
  assert_strings_equal(string_value(string), "foo.", "string value");

  string_push_char(string, 'b');
  assert_equal(string_length(string), 5, "second push: string length");
  assert_strings_equal(string_value(string), "foo.b", "string value");

  string_push_char(string, 'a');
  assert_equal(string_length(string), 6, "third push: string length");
  assert_strings_equal(string_value(string), "foo.ba", "string value");

  string_push_char(string, 'r');
  assert_equal(string_length(string), 7, "fourth push: string length");
  assert_strings_equal(string_value(string), "foo.bar", "string value");

  string_push_char(string, '(');
  assert_equal(string_length(string), 8, "fifth push: string length");
  assert_strings_equal(string_value(string), "foo.bar(", "string value");
  assert_ints_equal(string_capacity(string), 8, "capacity");

  string_push_char(string, ')');
  assert_ints_equal(string_capacity(string), 32, "fifth push: capacity");
  assert_ints_equal(string_offset(string), 28, "offset"); // 64 real capacity - 8 length = 56, divide 2 = 28
  assert_equal(string_length(string), 9, "string length");
  assert_strings_equal(string_value(string), "foo.bar()", "string value");

  string_free(string);

  return NULL;
}

char *test_concat() {
  spec_describe("Pushing char arrays into to a string");

  String *string = String_create("foo");

  assert_ints_equal(string_capacity(string), 8, "capacity");

  string_add_chars(string, ".bar()");

  assert_equal(string_length(string), 9, "fifth push: string length");
  assert_strings_equal(string_value(string), "foo.bar()", "string value");
  assert_ints_equal(string_capacity(string), 32, "capacity");

  string_free(string);

  return NULL;
}

char *test_create_blank() {
  spec_describe("Creating an empty string, for use as a null pattern string");

  String *string = String_create_blank();

  assert_ints_equal(string_length(string), 0, "length");
  assert_ints_equal(string_capacity(string), 0, "capacity");

  string_free(string);

  return NULL;
}

char *test_duplication() {
  spec_describe("Duplicating string");

  String *string = String_create("Hello");
  String *duplicate = string_duplicate(string);

  assert_strings_equal(string_value(string), string_value(duplicate), "same value");
  assert_not_equal(string, duplicate, "different addresses");

  string_free(string);

  return NULL;
}

char *all_specs() {
  spec_setup("Brick String");

  run_spec(test_create_from_literal);
  run_spec(test_create_from_allocated);
  run_spec(test_accessing_by_index);
  run_spec(test_push_character);
  run_spec(test_concat);

  run_spec(test_create_blank);
  run_spec(test_duplication);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
