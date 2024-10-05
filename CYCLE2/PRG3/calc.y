%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%union {
    int num;
}

%token <num> NUMBER
%type <num> expression term factor

%% 

calculation:
    expression '\n' { printf("Result: %d\n", $1); }
    ;

expression:
    expression '+' term  { $$ = $1 + $3; }
    | expression '-' term { $$ = $1 - $3; }
    | term                 { $$ = $1; }
    ;

term:
    term '*' factor       { $$ = $1 * $3; }
    | term '/' factor     { 
        if ($3 == 0) {
            yyerror("Division by zero!");
            $$ = 0; 
        } else {
            $$ = $1 / $3; 
        }
    }
    | factor               { $$ = $1; }
    ;

factor:
    '(' expression ')'    { $$ = $2; }
    | NUMBER               { $$ = $1; }
    ;

%% 

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter an expression: ");
    return yyparse();
}
