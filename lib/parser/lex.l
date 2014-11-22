%{

#include <stdio.h>
#include "token.h"

%}

%%
\.\.\.?												{ printf("background operator\n"); }
\.														{ printf("attr operator\n"); }
;                         		{ printf("statement end\n"); }
\(                         		{ printf("open paren\n"); }
\)                         		{ printf("close paren\n"); }
,                         		{ printf("comma\n"); }
_                         		{ printf("deferred arg\n"); }
=                         		{ printf("local assign operator\n"); }
:                         		{ printf("attr assign operator\n"); }
->                         		{ printf("block declaration\n"); }
\{                         		{ printf("block start\n"); }
\}                         		{ printf("block end\n"); }
!                         		{ printf("not unary operator\n"); }
[\-=a-z_]+[=a-z0-9_\-]* 			{ printf("id: %s\n", yytext); }
[A-Z]+[A-Za-z0-9_\-]* 				{ printf("class id: %s\n", yytext); }
-?[0-9]+\.[0-9]+          		{ printf("floating-point number: %s\n", yytext); }
-?[0-9]\.[0-9]+(e|E)-?[0-9]+  { printf("floating-point number: %s\n", yytext); }
-?[0-9]+                  		{ printf("integer: %s\n", yytext); }
[\-=a-z0-9_]+[=a-z0-9_\-]* 		{ printf("id: %s\n", yytext); }
:[a-z0-9_]+[a-z0-9_\-]* 		  { printf("atom: %s\n", yytext); }
\"([^"]|\\.)*\"           		{ printf("string: %s\n", yytext); }
\'([^']|\\.)*\'           		{ printf("string: %s\n", yytext); }
\/\*[^*]*\*\/             		{ printf("block comment: %s\n", yytext); }
\/\/[^\n]*                		{ printf("line end comment: %s\n", yytext); }
\/.*\/[a-z]? 									{ printf("regex: %s\n", yytext); }
[\n]                      		{ printf("line end\n"); }
[^ \t]                    		{ printf("unknown token: %s\n", yytext);};
[ \t]                     		;
%%

int main() {
	yylex();
}
