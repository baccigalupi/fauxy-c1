%{
  #include <stdio.h>
  #include "../core/bit.h"

  extern int yylex(void);
  void yyerror(char const *s) { fprintf(stderr, "%s\n", s); }
%}

%define api.token.prefix { TOKEN_}

%define api.value.type { FauxyBit }

// bison outputs header and c files in right location
%file-prefix "lib/parser/parse"
%defines

%token ELIPSES DOT EQUAL_SIGN COLON
%token SEMICOLON LINE_END COMMA
%token STRING INTEGER FLOAT ATOM REGEX
%token ID CLASS_ID DEFERRED_ARGUMENT
%token BLOCK_DECLARATION OPEN_BRACE CLOSE_BRACE
%token OPEN_PAREN CLOSE_PAREN
%token NOT_OPERATOR

%start program

%%

program: expressions

expressions
  : expressions expression
  | expression
  ;

expression
  : literal
  | identifier
  | block
  | list
  // operator call
  // method call
  ;

literal
  : STRING
  | number
  | ATOM
  | REGEX
  ;

number
  : INTEGER
  | FLOAT
  ;

identifier
  : ID
  | CLASS_ID
  ;

/* need to add in commas and multiple args*/
/* need to disambiguate grouped statement*/
list
  : OPEN_PAREN expression CLOSE_PAREN
  ;

/* need to add optional argument/list passing */
block
  : BLOCK_DECLARATION OPEN_BRACE expressions CLOSE_BRACE
  ;

/* METHOD CALLS HERE, HOLY COW! */


%%
