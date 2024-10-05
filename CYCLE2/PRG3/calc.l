%{
#include "y.tab.h"
%}

%%
[0-9]+       { yylval = atoi(yytext); return NUMBER; }
[+\-*/]     { return yytext[0]; }
[ \t\n]     { /* Ignore whitespace */ }
.           { return yytext[0]; }  // Return other characters as is
%% 

int yywrap() {
    return 1;
}
