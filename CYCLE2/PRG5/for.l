%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

"for"           { return FOR; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
";"             { return SEMICOLON; }
"="             { return ASSIGN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"<"             { return LESS; }
">"             { return GREATER; }
"<="            { return LESSEQUAL; }
">="            { return GREATEREQUAL; }
"=="            { return EQUAL; }
"!="            { return NOTEQUAL; }
"++"            { return INCREMENT; }
"--"            { return DECREMENT; }
[a-zA-Z_][a-zA-Z0-9_]*  { return IDENTIFIER; }
[0-9]+          { return NUMBER; }
[ \t\n]         { /* Ignore whitespace */ }
.               { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
