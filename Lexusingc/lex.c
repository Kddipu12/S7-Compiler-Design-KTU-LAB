#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH 100
#define BUFFER_SIZE 1024

// Token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING_LITERAL,
    TOKEN_CHAR_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATION,
    TOKEN_UNKNOWN,
    TOKEN_END
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

// Keywords in C
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "include", "define"
};

// Function prototypes
Token getNextToken(const char **input);
void printToken(Token token);
int isKeyword(const char *str);
int isOperatorChar(char c);

int main() {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *input;
    Token token;
    
    // Open the input file
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the entire content of the file into buffer
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, fp);
    if (bytesRead == 0) {
        perror("Error reading file");
        fclose(fp);
        return EXIT_FAILURE;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    // Close the file
    fclose(fp);

    // Set the input pointer to the beginning of the buffer
    input = buffer;

    printf("Input: %s\n", input);
    printf("Tokens:\n");

    // Process the tokens from the input
    do {
        token = getNextToken((const char **)&input);
        printToken(token);
    } while (token.type != TOKEN_END);

    return 0;
}

// Function to get the next token from the input
Token getNextToken(const char **input) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';

    // Skip whitespace
    while (isspace(**input)) {
        (*input)++;
    }

    // End of input
    if (**input == '\0') {
        token.type = TOKEN_END;
        return token;
    }

    // String literal
    if (**input == '"') {
        int length = 0;
        (*input)++;
        while (**input != '"' && **input != '\0' && length < MAX_TOKEN_LENGTH - 1) {
            token.value[length++] = **input;
            (*input)++;
        }
        if (**input == '"') {
            (*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_STRING_LITERAL;
        return token;
    }

    // Character literal
    if (**input == '\'') {
        int length = 0;
        (*input)++;
        while (**input != '\'' && **input != '\0' && length < MAX_TOKEN_LENGTH - 1) {
            token.value[length++] = **input;
            (*input)++;
        }
        if (**input == '\'') {
            (*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_CHAR_LITERAL;
        return token;
    }

    // Identifier or keyword
    if (isalpha(**input) || **input == '_') {
        int length = 0;
        while ((isalnum(**input) || **input == '_') && length < MAX_TOKEN_LENGTH - 1) {
            token.value[length++] = **input;
            (*input)++;
        }
        token.value[length] = '\0';
        token.type = isKeyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return token;
    }

    // Number
    if (isdigit(**input)) {
        int length = 0;
        while (isdigit(**input) && length < MAX_TOKEN_LENGTH - 1) {
            token.value[length++] = **input;
            (*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    // Operators and punctuations
    if (isOperatorChar(**input) || ispunct(**input)) {
        token.value[0] = **input;
        token.value[1] = '\0';
        token.type = isOperatorChar(**input) ? TOKEN_OPERATOR : TOKEN_PUNCTUATION;
        (*input)++;
        return token;
    }

    // Unknown character
    token.value[0] = **input;
    token.value[1] = '\0';
    token.type = TOKEN_UNKNOWN;
    (*input)++;

    return token;
}

// Function to print the token
void printToken(Token token) {
    const char *typeStr;
    switch (token.type) {
        case TOKEN_KEYWORD:
            typeStr = "Keyword";
            break;
        case TOKEN_IDENTIFIER:
            typeStr = "Identifier";
            break;
        case TOKEN_NUMBER:
            typeStr = "Number";
            break;
        case TOKEN_STRING_LITERAL:
            typeStr = "String Literal";
            break;
        case TOKEN_CHAR_LITERAL:
            typeStr = "Char Literal";
            break;
        case TOKEN_OPERATOR:
            typeStr = "Operator";
            break;
        case TOKEN_PUNCTUATION:
            typeStr = "Punctuation";
            break;
        case TOKEN_UNKNOWN:
            typeStr = "Unknown";
            break;
        case TOKEN_END:
            typeStr = "End";
            break;
        default:
            typeStr = "Invalid";
            break;
    }
    printf("Token: %-15s Value: %s\n", typeStr, token.value);
}

// Function to check if a string is a keyword
int isKeyword(const char *str) {
    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperatorChar(char c) {
    return strchr("+-*/=<>!&|%^", c) != NULL;
}


*/
    
Input: int a,b,c;
a=b+c;
Tokens:
Token: Keyword         Value: int
Token: Identifier      Value: a
Token: Punctuation     Value: ,
Token: Identifier      Value: b
Token: Punctuation     Value: ,
Token: Identifier      Value: c
Token: Punctuation     Value: ;
Token: Identifier      Value: a
Token: Operator        Value: =
Token: Identifier      Value: b
Token: Operator        Value: +
Token: Identifier      Value: c
Token: Punctuation     Value: ;
Token: End             Value: 
*/
