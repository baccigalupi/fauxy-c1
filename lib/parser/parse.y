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
%right EQUAL_SIGN COLON
%token SEMICOLON LINE_END COMMA
%token STRING EVAL_STRING INTEGER FLOAT ATOM REGEX
%token ID CLASS_ID DEFERRED_ARGUMENT
%left  ELIPSES DOT
%token BLOCK_DECLARATION OPEN_BRACE CLOSE_BRACE
%token OPEN_PAREN CLOSE_PAREN
%token NOT_OPERATOR

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
  : literal
  | identifier
  | block
  | list
  /*
  | operator_call
  | method_call
  */
  ;

expression
  : unterminated_expression expression_end
  ;

literal
  : string { printf("String \n");}
  | number
  | ATOM   { printf("Atom \n"); }
  | REGEX  { printf("Regex \n"); }
  | TRUE   { printf("true\n"); }
  | FALSE  { printf("false\n"); }
  | NIL    { printf("nil\n"); }
  ;

string
  : STRING
  | EVAL_STRING
  ;

number
  : INTEGER { printf("Integer \n");}
  | FLOAT   { printf("Float \n");}
  ;


identifier
  : ID        { printf("Id \n");}
  | CLASS_ID  { printf("Class Id \n");}
  ;


list
  : OPEN_PAREN list_elements CLOSE_PAREN
  ;

list_elements
  :
  | unterminated_expression
  | unterminated_expression COMMA list_elements
  ;


block
  : BLOCK_DECLARATION OPEN_BRACE expressions CLOSE_BRACE { printf("block\n"); }
  | BLOCK_DECLARATION list OPEN_BRACE expressions CLOSE_BRACE { printf("block with args\n"); }
  ;

/*
operator_call
  : unterminated_expression identifier unterminated_expression { printf("operator expression\n"); }
  ;

method_call
  : unterminated_expression DOT identifier { printf("method call\n"); }
  | unterminated_expression DOT identifier list { printf("method call with arguments\n"); }
  ;
  */
%%
