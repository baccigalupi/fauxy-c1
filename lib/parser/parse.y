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
%parse-param { FxP_LexWrapper *state }
%parse-param { FxP_ParserContext *context }

%{
  #include "parse.tab.h"
  #include "lex.yy.h"

  static void yyerror(YYLTYPE *location, FxP_LexWrapper *state, FxP_ParserContext *context, const char *s) {
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
  | function { printf("function\n"); }
  | method_call { $$ = $1; }
  | local_assignment { printf("local assign\n"); }
  | colonized_statement { printf("attr assign\n"); }
  | export_expression { printf("export expression"); }
  | list
  ;

grouped_statement
  : OPEN_PAREN CLOSE_PAREN                          { $$ = FxP_GroupedExpression_create(NULL); }
  | OPEN_PAREN unterminated_expression CLOSE_PAREN  { $$ = FxP_GroupedExpression_create($2); }
  ;

list
  : grouped_statement                             { $$ = fxp_list_convert($1); }
  | OPEN_PAREN DEFERRED_ARGUMENT CLOSE_PAREN      { $$ = FxP_List_create_deferred(); }
  | OPEN_PAREN list_elements CLOSE_PAREN          { $$ = $1; }
  ;

list_element
  : DEFERRED_ARGUMENT                             { $$ = FxP_Literal_create(NULL, TOKEN_DEFERRED_ARGUMENT); }
  | unterminated_expression                       { $$ = $1; }
  ;

list_elements
  : list_element COMMA list_element               { $$ = FxP_List_create_double($1, $3); }
  | list_element COMMA list_elements              { $$ = fxp_list_unshift($2, $1); }
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
  : unterminated_expression expression_end { fxp_parser_context_push(context, $1); }
  | expression_end
  ;

literal
  : STRING        { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_STRING); }
  | EVAL_STRING   { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_EVAL_STRING); }
  | INTEGER       { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_INTEGER); }
  | FLOAT         { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_FLOAT); }
  | SYMBOL        { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_SYMBOL); }
  | REGEX         { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_REGEX); }
  | TRUE          { $$ = FxP_Literal_create(NULL, TOKEN_TRUE); }
  | FALSE         { $$ = FxP_Literal_create(NULL, TOKEN_FALSE); }
  | NIL           { $$ = FxP_Literal_create(NULL, TOKEN_NIL); }
  ;

lookup
  : id_lookup     { $$ = $1; }
  | CLASS_ID      { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_CLASS_ID); }
  ;

id_lookup
  : ID           { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  ;

operator // for precedence
  : AND           { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  | OR            { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  ;

function
  : BLOCK_DECLARATION OPEN_BRACE expressions CLOSE_BRACE
  | BLOCK_DECLARATION list OPEN_BRACE expressions CLOSE_BRACE
  ;

implicit_method_call
  : id_lookup list                                            { $$ = FxP_MethodCall_create_implicit($1, $2); }
  ;

operator_call
  : unterminated_expression id_lookup unterminated_expression { $$ = FxP_MethodCall_create_operator($1, $2, $3); }
  | unterminated_expression operator unterminated_expression  { $$ = FxP_MethodCall_create_operator($1, $2, $3); }
  ;

dot_method_call
  : unterminated_expression DOT implicit_method_call          { $$ = fxp_method_call_convert_implicit($3, $1); }
  | unterminated_expression DOT id_lookup                     { $$ = FxP_MethodCall_create_no_args($1, $3); }
  ;

function_method_call
  : dot_method_call function                                  { $$ = fxp_method_call_add_function_argument($1, $2); }
  ;

method_call // pass along already constructed method expression
  : operator_call        { $$ = $1; }
  | dot_method_call      { $$ = $1; }
  | function_method_call    { $$ = $1; }
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
