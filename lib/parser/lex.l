%{
	#include <stdio.h>
	#include "lex_wrapper.h"
	#include "bit.h"
	#include "parse.tab.h"

	#define ParseObject_wrap(T, S) *yylval = FxP_Bit_create(T, S); return T
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
"and"													{ return TOKEN_AND; }
"&&"													{ return TOKEN_AND; }
"or"													{ return TOKEN_OR; }
"||"													{ return TOKEN_OR; }
"..."													{ return TOKEN_ELIPSES; }
".."													{ return TOKEN_ELIPSES; }
{BREAK_SPACE}"."{BREAK_SPACE}	{ return TOKEN_DOT; }
";"                         	{ return TOKEN_SEMICOLON; }
"("{BREAK_SPACE}              { return TOKEN_OPEN_PAREN; }
{BREAK_SPACE}")"              { return TOKEN_CLOSE_PAREN; }
{BREAK_SPACE}","{BREAK_SPACE} { return TOKEN_COMMA; }
"_"                         	{ return TOKEN_DEFERRED_ARGUMENT; }
"="                         	{ return TOKEN_EQUAL_SIGN; }
":"                         	{ return TOKEN_COLON; }
"->"                         	{ return TOKEN_FUNCTION_DECLARATION; }
"{"                         	{ return TOKEN_OPEN_BRACE; }
"}"                         	{ return TOKEN_CLOSE_BRACE; }
"!"                         	{ return TOKEN_NOT; }
\/\*(.|\n)*\*\/             	{ /* comment bracketed, treat as white space */ }
\/\/[^\n]*                		{ /* terminating comment, treat as white space */ }
{BREAK}	                      { return TOKEN_LINE_END; }
[ \t]                     		{ /* white space, move along */ }

[A-Z]+{CLASS_SUFFIX} 					  { ParseObject_wrap(TOKEN_CLASS_ID, yytext); }
-?[0-9]+\.[0-9]+          			{ ParseObject_wrap(TOKEN_FLOAT, yytext); }
-?[0-9]\.[0-9]+(e|E)-?[0-9]+  	{ ParseObject_wrap(TOKEN_FLOAT, yytext); }
-?[0-9]+                  			{ ParseObject_wrap(TOKEN_INTEGER, yytext); }
{ID_PREFACE}+[a-z0-9_\-\=]*[!?]? { ParseObject_wrap(TOKEN_ID, yytext); }
:[a-z0-9_]+[a-z0-9_\-]* 		  	{ ParseObject_wrap(TOKEN_SYMBOL, yytext); }
\/.*\/[a-z]? 										{ ParseObject_wrap(TOKEN_REGEX, yytext); }
\"([^"]|\\.)*\"           			{ ParseObject_wrap(TOKEN_EVAL_STRING, yytext); }
\'([^']|\\.)*\'           			{ ParseObject_wrap(TOKEN_STRING, yytext); }

{ID_PREFACE}+{CLASS_SUFFIX}			{ printf("illegal id: %s\n", yytext); }
.                    						{ printf("unknown token: %s\n", yytext); }
