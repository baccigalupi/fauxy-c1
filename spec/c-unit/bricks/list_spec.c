#include "../../../lib/bricks/_bricks.h"
#include "../lib/spec.h"

char *test_fxb_list_first_push() {
  spec_describe("Pushing first element");
  FxB_List *list = FxB_List_create();
  char *str = "first";

  fxb_list_push(list, str);

  assert_strings_equal(fxb_list_first(list), str,   "first node value set");
  assert_strings_equal(fxb_list_last(list) , str,   "last node value set");
  assert_ints_equal(fxb_list_length(list), 1,    "list length");
  assert_equal(list->first, list->last, "list node is last node");
  assert_equal(list->first->next, NULL, "first node next is null");
  assert_equal(list->first->prev, NULL, "first node prev is null");

  fxb_list_free(list);

  return NULL;
}

char *test_list_second_push() {
  spec_describe("Pushing a second element");

  FxB_List *list = FxB_List_create();
  char *str =  "first";
  char *str_2 = "second";

  fxb_list_push(list, str);
  fxb_list_push(list, str_2);

  assert_strings_equal(fxb_list_last(list), str_2, "last value");
  assert_ints_equal(fxb_list_length(list), 2,      "list length");
  assert_equal(list->first->next, list->last, "first node points next to last node");
  assert_equal(list->last->prev, list->first, "last node points prev to first node");

  fxb_list_free(list);

  return NULL;
}

char *test_list_additional_pushes() {
  spec_describe("Pushing additional times");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";
  char *str_3 = "third";

  fxb_list_push(list, str_1);
  fxb_list_push(list, str_2);
  fxb_list_push(list, str_3);

  // basic data
  assert_strings_equal(fxb_list_first(list), str_1, "first value");
  assert_strings_equal(fxb_list_last(list), str_3,  "last value");
  assert_ints_equal(fxb_list_length(list), 3,     "list length");

  // connections between nodes
  FxB_Node *first_node =  list->first;
  FxB_Node *middle_node = list->first->next;
  FxB_Node *last_node =   list->last;

  assert_strings_equal(middle_node->value, str_2,         "middle value");

  assert_equal(middle_node->prev, first_node,     "connection middle node to previous");
  assert_equal(middle_node->next, last_node,      "connection middle node to next");
  assert_equal(last_node->prev, middle_node,      "connection last node to middle node");

  fxb_list_free(list);

  return NULL;
}

char *test_fxb_list_pop() {
  spec_describe("Popping once");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";
  char *str_3 = "third";

  fxb_list_push(list, str_1);
  fxb_list_push(list, str_2);
  fxb_list_push(list, str_3);

  char *value = fxb_list_pop(list);
  assert_strings_equal(value, str_3,           "return value");
  assert_ints_equal(fxb_list_length(list), 2,    "decrement count");
  assert_strings_equal(fxb_list_last(list), str_2, "remove last node");
  assert_equal(list->last->next, NULL, "nullify reference to next node on last node");

  fxb_list_free(list);

  return NULL;
}

char *test_multiple_pops() {
  spec_describe("Multiple pops");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";
  char *str_3 = "third";

  fxb_list_push(list, str_1);
  fxb_list_push(list, str_2);
  fxb_list_push(list, str_3);

  char *value = fxb_list_pop(list);
  assert_ints_equal(fxb_list_length(list), 2,    "decrement list count");
  value = fxb_list_pop(list);
  assert_ints_equal(fxb_list_length(list), 1,    "decrement list count");
  value = fxb_list_pop(list);
  assert_ints_equal(fxb_list_length(list), 0,    "decrement list count");

  assert_strings_equal(value, str_1,           "return value");
  assert_equal(fxb_list_first(list), NULL, "nullify first");
  assert_equal(fxb_list_last(list), NULL,  "nullify last");

  value = fxb_list_pop(list); // to check that there isn't a memory error

  fxb_list_free(list);

  return NULL;
}

char *test_fxb_list_unshift() {
  spec_describe("Unshift");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";

  fxb_list_unshift(list, str_1);

  assert_strings_equal(fxb_list_first(list), str_1, "first value");
  assert_strings_equal(fxb_list_last(list) , str_1, "last value");
  assert_ints_equal(fxb_list_length(list), 1,     "list length");
  assert_equal(list->first, list->last, "first and last same");
  assert_equal(list->first->next, NULL, "first next is null");
  assert_equal(list->first->prev, NULL, "last prev is null");

  fxb_list_free(list);

  return NULL;
}

char *test_fxb_list_unshift_second_time() {
  spec_describe("Second unshift");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";

  fxb_list_unshift(list, str_1);
  fxb_list_unshift(list, str_2);

  assert_ints_equal(fxb_list_length(list), 2,     "list length");
  assert_strings_equal(fxb_list_last(list) , str_1, "last value");
  assert_strings_equal(fxb_list_first(list), str_2, "first value");

  assert_equal(list->first->next, list->last, "first node points to the next");
  assert_equal(list->last->prev, list->first, "last node to points to the previous");

  fxb_list_free(list);

  return NULL;
}

char *test_fxb_list_unshift_additional_time() {
  spec_describe("Unshift additional times");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";
  char *str_3 = "third";

  fxb_list_unshift(list, str_1);
  fxb_list_unshift(list, str_2);
  fxb_list_unshift(list, str_3);

  assert_ints_equal(fxb_list_length(list), 3,       "list length");
  assert_strings_equal(fxb_list_last(list) , str_1, "last value");
  assert_strings_equal(fxb_list_first(list), str_3, "first value");

  // connections between nodes
  FxB_Node *first_node =  list->first;
  FxB_Node *middle_node = list->first->next;
  FxB_Node *last_node =   list->last;

  assert_strings_equal(middle_node->value, str_2,         "middle value");

  assert_equal(middle_node->prev, first_node,     "connect middle node to previous");
  assert_equal(middle_node->next, last_node,      "connect middle node to next");
  assert_equal(last_node->prev, middle_node,      "connect last node to middle node");

  fxb_list_free(list);

  return NULL;
}

char *test_fxb_list_shift() {
  spec_describe("Shift");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";
  char *str_3 = "third";

  fxb_list_push(list, str_1);
  fxb_list_push(list, str_2);
  fxb_list_push(list, str_3);

  char *value = fxb_list_shift(list);
  assert_strings_equal(value, str_1,           "return value");
  assert_ints_equal(fxb_list_length(list), 2,     "decrement count");
  assert_strings_equal(fxb_list_first(list), str_2, "different first value");

  fxb_list_free(list);

  return NULL;
}

char *test_multiple_shifts() {
  spec_describe("Multiple shifts");
  FxB_List *list = FxB_List_create();
  char *str_1 = "first";
  char *str_2 = "second";
  char *str_3 = "third";

  fxb_list_push(list, str_1);
  fxb_list_push(list, str_2);
  fxb_list_push(list, str_3);

  char *value = fxb_list_shift(list);
  assert_ints_equal(fxb_list_length(list), 2,    "list count");
  value = fxb_list_shift(list);
  assert_ints_equal(fxb_list_length(list), 1,    "list count");
  value = fxb_list_shift(list);

  assert_strings_equal(value, str_3,      "return value");
  assert_ints_equal(fxb_list_length(list), 0, "decrement length");
  assert_equal(list->first, NULL,         "nullify first");
  assert_equal(list->last, NULL,          "nullify last");

  value = fxb_list_shift(list); // to make sure there is no memory error

  fxb_list_free(list);

  return NULL;
}

char *test_clear_and_destroy() {
  spec_describe("Clear and destroy");
  FxB_List *list = FxB_List_create();

  // can't deallocate what you haven't allocated!
  char *str_1 = calloc(10, sizeof(char));
  strcat(str_1, "first");
  char *str_2 = calloc(10, sizeof(char));
  strcat(str_2, "second");
  char *str_3 = calloc(10, sizeof(char));
  strcat(str_3, "third");

  fxb_list_push(list, str_1);
  fxb_list_push(list, str_2);
  fxb_list_push(list, str_3);

  fxb_list_r_free(list); // just sees that it works without fail

  return NULL;
}

char *all_specs() {
  spec_setup("Brick Double Linked FxB_List");

  run_spec(test_fxb_list_first_push);
  run_spec(test_list_second_push);
  run_spec(test_list_additional_pushes);

  run_spec(test_fxb_list_pop);
  run_spec(test_multiple_pops);

  run_spec(test_fxb_list_unshift);
  run_spec(test_fxb_list_unshift_second_time);
  run_spec(test_fxb_list_unshift_additional_time);

  run_spec(test_fxb_list_shift);
  run_spec(test_multiple_shifts);

  run_spec(test_clear_and_destroy);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
