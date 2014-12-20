%{
  #include <stdio.h>

  #include "parser_state.h"
  #include "expressions.h"
  #include "bit.h"
%}

// bison outputs header and c files in right location
%file-prefix "lib/parser/parse"
%defines

%error-verbose

%locations

%define api.token.prefix { TOKEN_}
%define api.value.type { FauxyBit * }

%pure-parser
%lex-param { void *scanner }
%parse-param { FxParserState *state }
%parse-param { Array *stack }

%{
  #include "parse.tab.h"
  #include "lex.yy.h"

  static void yyerror(YYLTYPE *location, FxParserState *state, Array *stack, const char *s) {
    fprintf(stderr, "line %d:%d error %s\n", location->first_line, location->first_column, s);
  }

  #define YYLEX_PARAM state->scanner
  #define scanner     YYLEX_PARAM
%}

%token TRUE FALSE NIL
%right EQUAL_SIGN COLON EXPORT // import
%token SEMICOLON LINE_END COMMA
%token STRING EVAL_STRING INTEGER FLOAT ATOM REGEX
%token ID CLASS_ID DEFERRED_ARGUMENT
%left  ELIPSES DOT
%token BLOCK_DECLARATION OPEN_BRACE CLOSE_BRACE
%token OPEN_PAREN CLOSE_PAREN
%left  AND OR
%token NOT

%start program

%%

program: expressions

expressions
  : /* empty, so that -> {}  works */
  | expressions expression
  ;

expression_end
  : LINE_END
  | SEMICOLON
  ;

unterminated_expression
  : literal { printf("literal\n"); }
  | lookup { printf("lookup\n"); }
  | block { printf("block\n"); }
  | list { printf("list\n"); }
  | method_call
  | implicit_method_call /* conflicts galore! */ { printf("implicit call\n"); }
  | local_assignment { printf("local assign\n"); }
  | attr_assignment { printf("attr assign\n"); }
  | export_expression { printf("export expression"); }
  ;

expression
  : unterminated_expression expression_end { printf("terminating expression\n"); }
  | expression_end
  ;

literal
  : string
  | number
  | ATOM
  | REGEX
  | TRUE
  | FALSE
  | NIL
  ;

string
  : STRING
  | EVAL_STRING
  ;

number // add literal to current statement
  : INTEGER
  | FLOAT
  ;


lookup // add lookup statement to current statement
  : ID
  | CLASS_ID
  ;


list
  : OPEN_PAREN list_elements CLOSE_PAREN
  ;

list_elements
  :
  | unterminated_expression
  | DEFERRED_ARGUMENT
  | unterminated_expression COMMA list_elements
  ;

block
  : BLOCK_DECLARATION OPEN_BRACE expressions CLOSE_BRACE
  | BLOCK_DECLARATION list OPEN_BRACE expressions CLOSE_BRACE
  ;

implicit_method_call
  : ID unterminated_expression
  ;

binary_operator_call
  : unterminated_expression implicit_method_call
  | unterminated_expression AND unterminated_expression
  | unterminated_expression OR unterminated_expression
  ;

standard_method_call /* ambiguity of implicit method call adds conflicts */
  : unterminated_expression DOT implicit_method_call
  | unterminated_expression DOT ID
  ;

method_call
  : binary_operator_call { printf("binary operator\n"); }
  | standard_method_call { printf("method call\n"); }
  | block_method_call { printf("method with block\n"); }
  ;

block_method_call
  : standard_method_call block
  ;

local_assignment
  : ID EQUAL_SIGN unterminated_expression
  ;

attr_assignment
  : ID COLON unterminated_expression
  ;

export_expression
  : EXPORT unterminated_expression
  ;
%%
