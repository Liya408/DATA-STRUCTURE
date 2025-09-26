#include <stdio.h>
#include <stdlib.h>
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};
int isDigit(char c) {
    return c >= '0' && c <= '9';
}
int isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
struct Node* parseExpression(char** expr);
struct Node* parseFactor(char** expr) {
    while(**expr == ' ') (*expr)++;

    if(**expr == '(') {
        (*expr)++;
        struct Node* node = parseExpression(expr);
        if (**expr == ')') {
            (*expr)++;
        }
        return node;
    }else if (isDigit(**expr) || isAlpha(**expr)) {
        struct Node* node = newNode(**expr);
        (*expr)++;
        return node;
    }
    return NULL;
}
struct Node* parseExpression(char** expr) {
    struct Node* left = parseFactor(expr);

    while(1) {
        while(**expr == ' ') (*expr)++;

        char op = **expr;
        if(op =='+'||op =='-'||op =='*'||op =='/') {
            (*expr)++;
            struct Node* right = parseFactor(expr);
            struct Node* new_root = newNode(op);
            new_root->left = left;
            new_root->right = right;
            left = new_root;
        }else{
            break;
        }
    }

    return left;
}
void printPrefix(struct Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
void printPostfix(struct Node* root) {
    if (root != NULL) {
        printPostfix(root->left);
        printPostfix(root->right);
        printf("%c ", root->data);
    }
}
int main() {
    char expr[100];

    printf("Enter the expression with variables:\n");
    fgets(expr, sizeof(expr), stdin);
    int i = 0;
    while (expr[i] != '\0') {
        if (expr[i] == '\n') {
            expr[i] = '\0';
            break;
        }
        i++;
    }
    char* p = expr;
    struct Node* root = parseExpression(&p);

    if (root == NULL) {
        printf("Invalid expression!\n");
        return 1;
    }
    printf("Prefix notation: ");
    printPrefix(root);
    printf("\n");

    printf("Postfix notation: ");
    printPostfix(root);
    printf("\n");

    return 0;
}
