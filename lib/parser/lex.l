%{
	#include <stdio.h>
	#include "lex_wrapper.h"
	#include "bit.h"
	#include "parse.tab.h"

  #define YY_USER_ACTION          yylloc->first_line    = yylineno + 1;        \
                                  yylloc->last_line     = yylineno + 1;        \
                                  yylloc->first_column  = yycolumn + 1;        \
                                  yylloc->last_column   = yycolumn + yyleng;   \
                                  yycolumn              = yycolumn + yyleng;

  #define FX_LexDebugLocations()  printf("\"%s\": start (%d, %d), end: (%d, %d)\n", yytext, yylloc->first_column, yylloc->first_line, yylloc->last_column, yylloc->last_line)

  #define FX_LexToken(T)          return T


	#define FX_LexStringBit(T, S)   *yylval = FxP_Bit_string_create(S);   FX_LexToken(T);
	#define FX_LexIntegerBit(T, S)  *yylval = FxP_Bit_integer_create(S);  FX_LexToken(T);
	#define FX_LexDecimalBit(T, S)  *yylval = FxP_Bit_decimal_create(S);  FX_LexToken(T);
	#define FX_LexExponentBit(T, S) *yylval = FxP_Bit_exponent_create(S); FX_LexToken(T);
%}

%option reentrant
%option noyywrap
%option header-file="lib/parser/lex.yy.h"
%option bison-bridge
%option bison-locations
%option yylineno

ID_PREFACE 	[\\/\=\-\*\^~@<>%`+&a-z0-9_]
CLASS_SUFFIX [A-Za-z0-9_\-]*
BREAK [\n]*
SPACE ([ \t]*)?
BREAK_SPACE ([ \t]*)?[\n]*([ \t]*)?

%%

"true"												    { FX_LexToken(TOKEN_TRUE); }
"false"												    { FX_LexToken(TOKEN_FALSE); }
"import"											    { FX_LexToken(TOKEN_IMPORT); }
"native"											    { FX_LexToken(TOKEN_NATIVE); }
"and"													    { FX_LexStringBit(TOKEN_AND, yytext); }
"&&"													    { FX_LexStringBit(TOKEN_AND, "and"); }
"or"													    { FX_LexStringBit(TOKEN_OR, yytext); }
"||"													    { FX_LexStringBit(TOKEN_OR, "or"); }
"="													      { FX_LexStringBit(TOKEN_EQUALITY, "="); }
"=="													    { FX_LexStringBit(TOKEN_STRICT_EQUALITY, "=="); }
"..."													    { FX_LexToken(TOKEN_ELIPSES); }
".."													    { FX_LexToken(TOKEN_ELIPSES); }
{BREAK_SPACE}"."{BREAK_SPACE}	    { FX_LexToken(TOKEN_DOT); }
";"                         	    { FX_LexToken(TOKEN_SEMICOLON); }
"("{BREAK_SPACE}                  { FX_LexToken(TOKEN_OPEN_PAREN); }
{BREAK_SPACE}")"                  { FX_LexToken(TOKEN_CLOSE_PAREN); }
{BREAK_SPACE}","{BREAK_SPACE}     { FX_LexToken(TOKEN_COMMA); }
"_"                         	    { FX_LexToken(TOKEN_DEFERRED_ARGUMENT); }
":"                         	    { FX_LexToken(TOKEN_COLON); }
"->"                         	    { FX_LexToken(TOKEN_FUNCTION_DECLARATION); }
"{"                         	    { FX_LexToken(TOKEN_OPEN_BRACE); }
"}"                         	    { FX_LexToken(TOKEN_CLOSE_BRACE); }
"!"                         	    { FX_LexStringBit(TOKEN_NOT, yytext); }
"?"                               { FX_LexStringBit(TOKEN_ID, yytext); }
\/\*(.|\n)*\*\/             	    { /* comment bracketed, treat as white space */ }
\/\/[^\n]*                		    { /* terminating comment, treat as white space */ }
{BREAK}	                          { FX_LexToken(TOKEN_LINE_END); }
<<EOF>>												    { FX_LexToken(TOKEN_EOF); }
[ \t]*                     		    { /* white space, move along */ }

[A-Z]+{CLASS_SUFFIX} 					  	{ FX_LexStringBit(TOKEN_CLASS_ID, yytext); }

-?[0-9]+\.[0-9]+          				{ FX_LexDecimalBit(TOKEN_FLOAT, yytext); }
-?[0-9]\.[0-9]+(e|E)-?[0-9]+  		{ FX_LexExponentBit(TOKEN_FLOAT, yytext); }
-?[0-9]+                  				{ FX_LexIntegerBit(TOKEN_INTEGER, yytext); }

{ID_PREFACE}+[a-z0-9_\-\=]*[!?]? 	{ FX_LexStringBit(TOKEN_ID, yytext); }
\/.*\/[a-z]? 											{ FX_LexStringBit(TOKEN_REGEX, yytext); }
\"([^"]|\\.)*\"           				{ FX_LexStringBit(TOKEN_EVAL_STRING, yytext); }
\'([^']|\\.)*\'           				{ FX_LexStringBit(TOKEN_STRING, yytext); }

{ID_PREFACE}+{CLASS_SUFFIX}				{ FX_LexStringBit(TOKEN_LEX_ERROR_ILLEGAL_VARIABLE, yytext); }
.                    							{ FX_LexStringBit(TOKEN_LEX_ERROR_UNKNOWN_TOKEN, yytext); }
