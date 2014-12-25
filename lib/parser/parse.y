%{
  #include <stdio.h>

  #include "lex_wrapper.h"
  #include "parser_context.h"
  #include "expressions.h"
  #include "bit.h"
%}

// bison outputs header and c files in right location
%file-prefix "lib/parser/parse"
%defines

%error-verbose

%locations

%define api.token.prefix { TOKEN_}
%define api.value.type { void * }

%pure-parser
%lex-param   { void *scanner }
%parse-param { FxLexWrapper *state }
%parse-param { FxParserContext *context }

%{
  #include "parse.tab.h"
  #include "lex.yy.h"

  static void yyerror(YYLTYPE *location, FxLexWrapper *state, FxParserContext *context, const char *s) {
    fprintf(stderr, "line %d:%d error %s\n", location->first_line, location->first_column, s);
  }

  #define YYLEX_PARAM state->scanner
  #define scanner     YYLEX_PARAM
%}

%token TRUE FALSE NIL
%right EQUAL_SIGN COLON EXPORT // import
%token SEMICOLON LINE_END COMMA
%token STRING EVAL_STRING INTEGER FLOAT SYMBOL REGEX
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
  : literal { $$ = $1; }
  | lookup  { $$ = $1; }
  | block { printf("block\n"); }
  | method_call { $$ = $1; }
  | local_assignment { printf("local assign\n"); }
  | colonized_statement { printf("attr assign\n"); }
  | export_expression { printf("export expression"); }
  | list
  ;

grouped_statement
  : OPEN_PAREN CLOSE_PAREN                          { $$ = FxGroupedExpression_create(NULL); }
  | OPEN_PAREN unterminated_expression CLOSE_PAREN  { $$ = FxGroupedExpression_create($2); }
  ;

list
  : grouped_statement                             { $$ = $1; }
  | OPEN_PAREN DEFERRED_ARGUMENT CLOSE_PAREN      // { $$ = FxLiteral_create(NULL, TOKEN_DEFERRED_ARGUMENT); }
  | OPEN_PAREN list_elements CLOSE_PAREN
  ;

list_element
  : DEFERRED_ARGUMENT
  | unterminated_expression
  ;

list_elements
  : list_element COMMA list_element
  | list_element COMMA list_elements
  ;

  /*
    Grouped statements vs arguments vs lists

    Grouped:
    (1 + 1) * 2
    (1 == foo) && (2 == bar)

    Arguments:
    foo(1 + 1)
    bar(2 == bar)
    zardoz(1 + 1, 2 == bar)

    Lists:
    (1 + 1)
    (1, 2, foo)
  */

expression
  : unterminated_expression expression_end { fx_parser_context_push(context, $1); }
  | expression_end
  ;

literal
  : STRING        { $$ = FxLiteral_create((FxBit *)$1, TOKEN_STRING); }
  | EVAL_STRING   { $$ = FxLiteral_create((FxBit *)$1, TOKEN_EVAL_STRING); }
  | INTEGER       { $$ = FxLiteral_create((FxBit *)$1, TOKEN_INTEGER); }
  | FLOAT         { $$ = FxLiteral_create((FxBit *)$1, TOKEN_FLOAT); }
  | SYMBOL        { $$ = FxLiteral_create((FxBit *)$1, TOKEN_SYMBOL); }
  | REGEX         { $$ = FxLiteral_create((FxBit *)$1, TOKEN_REGEX); }
  | TRUE          { $$ = FxLiteral_create(NULL, TOKEN_TRUE); }
  | FALSE         { $$ = FxLiteral_create(NULL, TOKEN_FALSE); }
  | NIL           { $$ = FxLiteral_create(NULL, TOKEN_NIL); }
  ;

lookup
  : id_lookup     { $$ = $1; }
  | CLASS_ID      { $$ = FxLiteral_create((FxBit *)$1, TOKEN_CLASS_ID); }
  ;

id_lookup
  : ID           { $$ = FxLiteral_create((FxBit *)$1, TOKEN_ID); }
  ;

operator // for precedence
  : AND           { $$ = FxLiteral_create((FxBit *)$1, TOKEN_ID); }
  | OR            { $$ = FxLiteral_create((FxBit *)$1, TOKEN_ID); }
  ;

block
  : BLOCK_DECLARATION OPEN_BRACE expressions CLOSE_BRACE
  | BLOCK_DECLARATION list OPEN_BRACE expressions CLOSE_BRACE
  ;

implicit_method_call
  : id_lookup list                                            { $$ = FxMethodCall_create_implicit($1, $2); }
  ;

operator_call
  : unterminated_expression id_lookup unterminated_expression { $$ = FxMethodCall_create_operator($1, $2, $3); }
  | unterminated_expression operator unterminated_expression  { $$ = FxMethodCall_create_operator($1, $2, $3); }
  ;

dot_method_call
  : unterminated_expression DOT implicit_method_call          { $$ = fx_method_call_convert_implicit($3, $1); }
  | unterminated_expression DOT id_lookup                     { $$ = FxMethodCall_create_no_args($1, $3); }
  ;

block_method_call
  : dot_method_call block // add block to arguments list
  ;

method_call // pass along already constructed method expression
  : operator_call        { $$ = $1; }
  | dot_method_call      { $$ = $1; }
  | block_method_call    { $$ = $1; }
  | implicit_method_call { $$ = $1; }
  ;

local_assignment
  : lookup EQUAL_SIGN unterminated_expression
  ;

/*
  either argument conditions in method def, named arguments, or local assignment:

  defining arguments:
    -> (x: x <= 1) { 1 }

  named arguments:
    Object.new(foo: 0, bar: 1)

  local assignment:
    foo: -> { Print.line 'foo' }
*/
colonized_statement
  : lookup COLON unterminated_expression
  ;

export_expression
  : EXPORT unterminated_expression
  ;
%%
