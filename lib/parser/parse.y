%{
  #include <stdio.h>

  #include "lex_wrapper.h"
  #include "parser_context.h"
  #include "expressions.h"
  #include "expression_inspect.h"
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
    fprintf(stderr, "ParseError: line %d:%d %s\n", location->first_line, location->first_column, s);
  }

  #define YYLEX_PARAM state->scanner
  #define scanner     YYLEX_PARAM
%}

%token TRUE FALSE
%right LOCAL_ASSIGN COLON IMPORT
%token SEMICOLON LINE_END COMMA
%token STRING EVAL_STRING INTEGER FLOAT REGEX
%token ID CLASS_ID DEFERRED_ARGUMENT
%left  ELIPSES DOT
%token FUNCTION_DECLARATION OPEN_BRACE CLOSE_BRACE
%token OPEN_PAREN CLOSE_PAREN
%left  AND OR EQUALITY STRICT_EQUALITY
%token NOT
%token EOF
%token LEX_ERROR_ILLEGAL_VARIABLE LEX_ERROR_UNKNOWN_TOKEN

%start program

%%

program: expressions

expressions
  : /* empty, so that -> {}  works */
  | expressions expression
  ;

expression
  : unterminated_expression expression_end  { fxp_parser_push_expression(context, $1); }
  | implicit_method_call expression_end     { fxp_parser_push_expression(context, $1); }
  | expression_end                          { }
  | unterminated_expression EOF             { fxp_parser_push_expression(context, $1); YYACCEPT; }
  | implicit_method_call EOF                { fxp_parser_push_expression(context, $1); YYACCEPT; }
  | lex_error                               { YYACCEPT; }
  | EOF                                     { YYACCEPT; }
  ;

expression_end
  : LINE_END
  | SEMICOLON
  ;

unterminated_expression
  : literal               { $$ = $1; }
  | lookup                { $$ = $1; }
  | function              { $$ = $1; }
  | method_call           { $$ = $1; }
  | local_assignment      { $$ = $1; }
  | colonized_expression  { $$ = $1; }
  | list                  { $$ = $1; }
  | import_expression     { $$ = $1; }
  ;

/* -------------------------
-- Expressions with parenthesis
*/
grouped_expression
  : OPEN_PAREN CLOSE_PAREN                          { $$ = FxP_Grouped_create(NULL); }
  | OPEN_PAREN unterminated_expression CLOSE_PAREN  { $$ = FxP_Grouped_create($2); }
  ;

list
  : grouped_expression                            { $$ = $1; }
  | OPEN_PAREN DEFERRED_ARGUMENT CLOSE_PAREN      { $$ = FxP_List_create_deferred(); }
  | OPEN_PAREN list_elements CLOSE_PAREN          { $$ = $2; }
  ;

list_elements
  : unterminated_expression COMMA unterminated_expression    { $$  = FxP_List_create_double($1, $3); }
  | unterminated_expression COMMA list_elements              { fxp_list_push((FxP_List *)$3, $1); $$ = $3; }
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

    FxB_Lists:
    (1 + 1)
    (1, 2, foo)
  */



/* ----------------------------
-- FUNCTION DEFINITION
*/

function_start
  : FUNCTION_DECLARATION OPEN_BRACE         {
                                              FxP_FunctionDefinition *function = FxP_FunctionDefinition_create_no_args();
                                              fxp_parser_context_push(context, fxp_function_definition_expressions(function));
                                              $$ = function;
                                            }
  | FUNCTION_DECLARATION list OPEN_BRACE    {
                                              FxP_FunctionDefinition *function = FxP_FunctionDefinition_create($2);
                                              fxp_parser_context_push(context, fxp_function_definition_expressions(function));
                                              $$ = function;
                                            }
  ;

function_expressions
  : expressions
  | unterminated_expression                                   { fxp_parser_push_expression(context, $1);}
  ;

function
  : function_start function_expressions CLOSE_BRACE           {
                                                                fxp_parser_context_pop(context);
                                                              }
  ;

/* ----------------------------
-- METHOD INVOCATIONS
*/

operator_call /* n + 3; -> {'foo' } >> a(_); (1, 2, 3) << 17 */
  : unterminated_expression id_lookup unterminated_expression       { $$ = FxP_MethodCall_create_args($1, $2, $3); }
  | unterminated_expression operator unterminated_expression        { $$ = FxP_MethodCall_create_args($1, $2, $3); }
  ;

dot_method_call /* Print.line "foo"; Print.line("foo"); Print.line */
  : unterminated_expression DOT id_lookup unterminated_expression   { $$ = FxP_MethodCall_create_args($1, $3, $4); }
  | unterminated_expression DOT id_lookup                           { $$ = FxP_MethodCall_create_no_args($1, $3); }
  ;

function_method_call
  : dot_method_call function                                        { $$ = fxp_method_call_add_function_definition_argument($1, $2); }
  ;

negation
  : NOT unterminated_expression   { $$ = FxP_MethodCall_create_negation($2, $1); }
  | NOT implicit_method_call      { $$ = FxP_MethodCall_create_negation($2, $1); }
  ;

method_call
  : operator_call           { $$ = $1; }
  | dot_method_call         { $$ = $1; }
  | function_method_call    { $$ = $1; }
  | negation                { $$ = $1; }
  ;

implicit_method_call /* puts "hello"; foo(1,2,3);  */
  : id_lookup unterminated_expression                               { $$ = FxP_MethodCall_create_implicit($1, $2); }
  ;

/* ----------------
** Assignment related expressions
*/

local_assignment
  : lookup LOCAL_ASSIGN unterminated_expression                 { $$ = FxP_LocalAssign_create($1, $2); }
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
colonized_expression
  : lookup COLON unterminated_expression                    { $$ = FxP_ColonExpression_create($1, $3); }
  | lookup COLON implicit_method_call                       { $$ = FxP_ColonExpression_create($1, $3); }
  ;

import_expression
  : IMPORT unterminated_expression                          { $$ = FxP_ImportExpression_create($2); }
  ;

/* ------------------
-- BASE Types
*/

literal
  : STRING        { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_STRING); }
  | EVAL_STRING   { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_EVAL_STRING); }
  | INTEGER       { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_INTEGER); }
  | FLOAT         { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_FLOAT); }
  | REGEX         { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_REGEX); }
  | TRUE          { $$ = FxP_Literal_create(NULL, TOKEN_TRUE); }
  | FALSE         { $$ = FxP_Literal_create(NULL, TOKEN_FALSE); }
  ;

lookup
  : id_lookup     { $$ = $1; }
  | CLASS_ID      { $$ = FxP_Lookup_create((FxP_Bit *)$1, TOKEN_CLASS_ID); }
  ;

id_lookup
  : ID            { $$ = FxP_Lookup_create((FxP_Bit *)$1, TOKEN_ID); }
  ;

operator /* for precedence */
  : AND             { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  | OR              { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  | EQUALITY        { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  | STRICT_EQUALITY { $$ = FxP_Literal_create((FxP_Bit *)$1, TOKEN_ID); }
  ;

lex_error
  : LEX_ERROR_ILLEGAL_VARIABLE          {
                                          fxp_parser_context_error_code(context) = TOKEN_LEX_ERROR_ILLEGAL_VARIABLE;
                                          yyerror(&(@1), state, context, "Illegal variable or method name");
                                        }
  | LEX_ERROR_UNKNOWN_TOKEN             {
                                          fxp_parser_context_error_code(context) = TOKEN_LEX_ERROR_UNKNOWN_TOKEN;
                                          yyerror(&(@1), state, context, "Unknown token");
                                        }
  ;

%%
