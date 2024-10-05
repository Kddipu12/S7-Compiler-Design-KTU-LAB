%{
#include <stdio.h>
%}

%token LETTER DIGIT

%%
variable:
    LETTER rest { printf("Valid variable\n"); }
    ;

rest:
    | rest LETTER
    | rest DIGIT
    ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
