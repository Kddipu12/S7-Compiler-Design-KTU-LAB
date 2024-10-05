%{
#include <stdio.h>
#include <stdlib.h>

// Include the AST node structure
#include "ast.h"

// Function to print the AST (for demonstration)
void print_ast(ASTNode* node, int level) {
    if (node) {
        for (int i = 0; i < level; i++) printf("  ");
        if (node->type == NODE_NUMBER) {
            printf("NUMBER: %d\n", node->value);
        } else {
            printf("OPERATOR: %s\n", 
                   node->type == NODE_ADD ? "+" :
                   node->type == NODE_SUBTRACT ? "-" :
                   node->type == NODE_MULTIPLY ? "*" :
                   "/");
        }
        print_ast(node->left, level + 1);
        print_ast(node->right, level + 1);
    }
}

%}

%union {
    int value; // for numbers
    ASTNode* node; // for AST nodes
}

%token <value> NUMBER
%type <node> calculation expression term factor

%%

// Grammar rules
calculation: expression '\n' {
    print_ast($1, 0); // Print the AST
    free($1); // Free the allocated AST memory
}
;

expression: expression '+' term {
    $$ = new_node(NODE_ADD, $1, $3, 0);
}
| expression '-' term {
    $$ = new_node(NODE_SUBTRACT, $1, $3, 0);
}
| term {
    $$ = $1;
}
;

term: term '*' factor {
    $$ = new_node(NODE_MULTIPLY, $1, $3, 0);
}
| term '/' factor {
    $$ = new_node(NODE_DIVIDE, $1, $3, 0);
}
| factor {
    $$ = $1;
}
;

factor: '(' expression ')' {
    $$ = $2; // Return the result of the inner expression
}
| NUMBER {
    $$ = new_node(NODE_NUMBER, NULL, NULL, $1); // Create a number node
}
;

%%

// Lexical analyzer (Flex)
#include <ctype.h>

int yylex(void);
void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter expressions:\n");
    return yyparse();
}

// Lexical analyzer implementation
int yylex(void) {
    int c;

    // Skip whitespace
    while ((c = getchar()) == ' ' || c == '\t' || c == '\n');

    if (isdigit(c)) {
        ungetc(c, stdin);
        int value;
        scanf("%d", &value);
        yylval.value = value;
        return NUMBER;
    }

    return c; // return operators and parentheses directly
}
