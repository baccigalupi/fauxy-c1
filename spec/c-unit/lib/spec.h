#ifndef _spec_h
#define _spec_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../../../lib/bricks/helpers.h"

#define spec_describe(S)          printf("\n%s %s %s\n", CONSOLE_ORANGE, S, CONSOLE_RESET)

#define spec_setup(S)             printf("\n%s Starting specs: %s %s\n", CONSOLE_ORANGE, S, CONSOLE_RESET);   \
                                  spec_description = NULL;                                                    \
                                  assertions_failed = 0;                                                      \
                                  assertions_passed = 0;                                                      \
                                  specs_run = 0;                                                              \

#define spec_teardown()           printf("\n%s Specs Run: %d, Assertions Passed: %d, Assertions Failed: %d %s\n\n", \
                                    CONSOLE_ORANGE, specs_run, assertions_passed, assertions_failed, CONSOLE_RESET);


#define print_status(S, COLOR)    (printf("  %s%s %s\n", COLOR, S, CONSOLE_RESET))
#define print_success(S)          print_status(S, CONSOLE_GREEN)
#define print_failure(S)          print_status(S, CONSOLE_RED)
#define print_location()          (printf("    file: '%s' line '%d'\n", __FILE__, __LINE__))

#define print_int_expectation(A, B)     (printf("    Expected %d to be %d\n", (int)A, (int)B))
#define print_float_expectation(A, B)   (printf("    Expected %f to be %f\n", (float)A, (float)B))
#define print_string_expectation(A, B)  (printf("    Expected '%s' to be '%s'\n", A, B))


#define assert_equal(A, B, S)     (                                                                 \
                                    ((A) == (B)) ?                                                  \
                                    ((++assertions_passed) && (print_success(S))) :                 \
                                    ((++assertions_failed), (print_failure(S)), (print_location())) \
                                  )

#define assert_not_equal(A, B, S) (                                                                 \
                                    ((A) != (B)) ?                                                  \
                                    ((++assertions_passed) && (print_success(S))) :                 \
                                    ((++assertions_failed), (print_failure(S)), (print_location())) \
                                  )

#define assert_ints_equal(A, B, S)    assert_equal(A, B, S); ((A) == (B)) ? 0 : print_int_expectation(A, B)
#define assert_floats_equal(A, B, S)  assert_equal(A, B, S); ((A) == (B)) ? 0 : print_float_expectation(A, B)

#define assert_strings_equal(A, B, S) (                                                                                                     \
                                        (strcmp(A, B)) == 0 ?                                                                               \
                                        ((++assertions_passed), (print_success(S))) :                                                       \
                                        ((++assertions_failed), (print_failure(S)), (print_location()), (print_string_expectation(A, B)))   \
                                      )

#define run_spec(S)                S(); specs_run++;

#define run_all_specs(S)  int main() {                              \
  S();                                                              \
  if (assertions_failed) {                                          \
    printf("%sFAILED: %s\n", CONSOLE_RED, CONSOLE_RESET);           \
  } else {                                                          \
    printf("%sALL TESTS PASSED%s\n", CONSOLE_GREEN, CONSOLE_RESET); \
    printf("------------------\n\n");                               \
  }                                                                 \
  exit(assertions_failed);                                          \
}

char  *spec_description;
int   assertions_passed;
int   assertions_failed;
int   specs_run;

#endif
