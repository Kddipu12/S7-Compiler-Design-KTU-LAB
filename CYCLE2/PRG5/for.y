%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IDENTIFIER NUMBER
%token FOR SEMICOLON LPAREN RPAREN LBRACE RBRACE
%token ASSIGN PLUS MINUS MULTIPLY DIVIDE
%token LESS GREATER LESSEQUAL GREATEREQUAL EQUAL NOTEQUAL
%token INCREMENT DECREMENT

%%

for_statement
    : FOR LPAREN initialization SEMICOLON condition SEMICOLON update RPAREN statement
    ;

initialization
    : assignment
    | /* empty */
    ;

condition
    : expression
    | /* empty */
    ;

update
    : assignment
    | increment_expression
    | /* empty */
    ;

assignment
    : IDENTIFIER ASSIGN expression
    ;

increment_expression
    : IDENTIFIER INCREMENT
    | IDENTIFIER DECREMENT
    | INCREMENT IDENTIFIER
    | DECREMENT IDENTIFIER
    ;

expression
    : IDENTIFIER
    | NUMBER
    | expression PLUS expression
    | expression MINUS expression
    | expression MULTIPLY expression
    | expression DIVIDE expression
    | expression LESS expression
    | expression GREATER expression
    | expression LESSEQUAL expression
    | expression GREATEREQUAL expression
    | expression EQUAL expression
    | expression NOTEQUAL expression
    | LPAREN expression RPAREN
    ;

statement
    : LBRACE statement_list RBRACE
    | assignment SEMICOLON
    | increment_expression SEMICOLON
    | /* empty */
    ;

statement_list
    : statement
    | statement_list statement
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    printf("Parsing complete.\n");
    return 0;
}
