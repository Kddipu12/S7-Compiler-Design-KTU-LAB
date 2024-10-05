#include <stdio.h>
#include <stdlib.h>

// Define the types of AST nodes
typedef enum { 
    NODE_NUMBER, 
    NODE_ADD, 
    NODE_SUBTRACT, 
    NODE_MULTIPLY, 
    NODE_DIVIDE 
} NodeType;

// Define the structure for AST nodes
typedef struct ASTNode {
    NodeType type;
    struct ASTNode* left;
    struct ASTNode* right;
    int value; // used for numbers
} ASTNode;

// Function to create a new AST node
ASTNode* new_node(NodeType type, ASTNode* left, ASTNode* right, int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->value = value;
    return node;
}
