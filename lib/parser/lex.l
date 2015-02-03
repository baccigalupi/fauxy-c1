%{
	#include <stdio.h>
	#include "lex_wrapper.h"
	#include "bit.h"
	#include "parse.tab.h"

	#define FX_LexStringBit(T, S)   *yylval = FxP_Bit_string_create(S);   return T
	#define FX_LexIntegerBit(T, S)  *yylval = FxP_Bit_integer_create(S);  return T
	#define FX_LexDecimalBit(T, S)  *yylval = FxP_Bit_decimal_create(S);  return T
	#define FX_LexExponentBit(T, S) *yylval = FxP_Bit_exponent_create(S); return T
%}

%option reentrant
%option noyywrap
%option header-file="lib/parser/lex.yy.h"
%option bison-bridge
%option bison-locations

ID_PREFACE 	[\\/\=\-\*\^~@<+&a-z0-9_]
CLASS_SUFFIX [A-Za-z0-9_\-]*
BREAK [\n]*
SPACE ([ \t]*)?
BREAK_SPACE ([ \t]*)?[\n]*([ \t]*)?

%%

"true"												{ return TOKEN_TRUE; }
"false"												{ return TOKEN_FALSE; }
"nil"													{ return TOKEN_NIL; }
"export"											{ return TOKEN_EXPORT; }
"and"													{ FX_LexStringBit(TOKEN_AND, "and"); }
"&&"													{ FX_LexStringBit(TOKEN_AND, "and"); }
"or"													{ FX_LexStringBit(TOKEN_OR, "or"); }
"||"													{ FX_LexStringBit(TOKEN_OR, "or"); }
"..."													{ return TOKEN_ELIPSES; }
".."													{ return TOKEN_ELIPSES; }
{BREAK_SPACE}"."{BREAK_SPACE}	{ return TOKEN_DOT; }
";"                         	{ return TOKEN_SEMICOLON; }
"("{BREAK_SPACE}              { return TOKEN_OPEN_PAREN; }
{BREAK_SPACE}")"              { return TOKEN_CLOSE_PAREN; }
{BREAK_SPACE}","{BREAK_SPACE} { return TOKEN_COMMA; }
"_"                         	{ return TOKEN_DEFERRED_ARGUMENT; }
"::"                         	{ return TOKEN_LOCAL_ASSIGN; }
":"                         	{ return TOKEN_COLON; }
"->"                         	{ return TOKEN_FUNCTION_DECLARATION; }
"{"                         	{ return TOKEN_OPEN_BRACE; }
"}"                         	{ return TOKEN_CLOSE_BRACE; }
"!"                         	{ FX_LexStringBit(TOKEN_NOT, "not"); }
\/\*(.|\n)*\*\/             	{ /* comment bracketed, treat as white space */ }
\/\/[^\n]*                		{ /* terminating comment, treat as white space */ }
{BREAK}	                      { return TOKEN_LINE_END; }
<<EOF>>												{ return TOKEN_EOF; }
[ \t]                     		{ /* white space, move along */ }

[A-Z]+{CLASS_SUFFIX} 					  	{ FX_LexStringBit(TOKEN_CLASS_ID, yytext); }

-?[0-9]+\.[0-9]+          				{ FX_LexDecimalBit(TOKEN_FLOAT, yytext); }
-?[0-9]\.[0-9]+(e|E)-?[0-9]+  		{ FX_LexExponentBit(TOKEN_FLOAT, yytext); }
-?[0-9]+                  				{ FX_LexIntegerBit(TOKEN_INTEGER, yytext); }

{ID_PREFACE}+[a-z0-9_\-\=]*[!?]? 	{ FX_LexStringBit(TOKEN_ID, yytext); }
:[a-z0-9_]+[a-z0-9_\-]* 		  		{ FX_LexStringBit(TOKEN_SYMBOL, yytext); }
\/.*\/[a-z]? 											{ FX_LexStringBit(TOKEN_REGEX, yytext); }
\"([^"]|\\.)*\"           				{ FX_LexStringBit(TOKEN_EVAL_STRING, yytext); }
\'([^']|\\.)*\'           				{ FX_LexStringBit(TOKEN_STRING, yytext); }

{ID_PREFACE}+{CLASS_SUFFIX}				{ printf("illegal id: %s\n", yytext); }
.                    							{ printf("unknown token: %s\n", yytext); }
