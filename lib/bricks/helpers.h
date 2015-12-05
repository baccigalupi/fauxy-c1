#ifndef __FxB_Helpers_h
#define __FxB_Helpers_h 1

#include <stdio.h>
#include <stdlib.h>

#define CONSOLE_RED      "\e[31m"
#define CONSOLE_GREEN    "\e[38;5;40m"
#define CONSOLE_ORANGE   "\e[40;38;5;214m"
#define CONSOLE_RESET    "\e[0m"

#define ERROR_MESSAGE         "%s[ERROR]%s (%s:%d) "
#define WARN_MESSAGE          "%s[WARN]%s (%s:%d) "
#define INFO_MESSAGE          "%s[INFO]%s (%s:%d) "

typedef enum { false, true }  Boolean;
#define SUCCESS               true
#define FAILURE               false

#define print_error(M)        fprintf(stderr, ERROR_MESSAGE M "\n", CONSOLE_RED, CONSOLE_RESET, __FILE__, __LINE__)
#define print_warning(M)      fprintf(stderr, WARN_MESSAGE M "\n", CONSOLE_ORANGE, CONSOLE_RESET, __FILE__, __LINE__)
#define print_info(M)         fprintf(stderr, INFO_MESSAGE M "\n", CONSOLE_ORANGE, CONSOLE_RESET, __FILE__, __LINE__)

#define MEMORY_ERROR        "Memory error"

#define verify(S)           if(!(S)) { goto error; }
#define verify_memory(S)    if(!(S)) { print_error(MEMORY_ERROR); goto error; }
#define verify_no_error(S)  (verify((S)->error))

#define fx_alloc(S)         (calloc(1, sizeof(S)))
#define fx_pfree(P)         ((P) != NULL) ? (free(P), ((P) = NULL)) : (NULL)

#define inspect(S)          (printf("%s\n", S), free(S))

#endif
