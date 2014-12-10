%{
  #include <stdio.h>
  #include "../core/bit.h"

  extern int yylex(void);
  void yyerror(char const *s) { fprintf(stderr, "%s\n", s); }
%}

%define parse.error verbose

%define api.token.prefix { TOKEN_}
%define api.value.type { FauxyBit }

// bison outputs header and c files in right location
%file-prefix "lib/parser/parse"
%defines

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
  | expressions unterminated_expression
  | expression_end
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
  | binary_operator_call { printf("binary operator\n"); }
  | method_call { printf("method call\n"); }
  | block_method_call { printf("method with block\n"); }
  | implicit_method_call /* adding this added 13 new conflicts! */ { printf("implicit call\n"); }
  | local_assignment { printf("local assign\n"); }
  | attr_assignment { printf("attr assign\n"); }
  | export_expression { printf("export expression"); }
  ;

expression
  : unterminated_expression expression_end
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

number
  : INTEGER
  | FLOAT
  ;


lookup
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

method_call /* ambiguity of implicit method call adds another 14 conflicts */
  : unterminated_expression DOT implicit_method_call
  | unterminated_expression DOT ID
  ;

block_method_call
  : method_call block
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
