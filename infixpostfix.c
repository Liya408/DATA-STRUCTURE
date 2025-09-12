#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>   
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = ch;
}

char pop() {
    if (top == -1)
        return '\0';
    return stack[top--];
}

char peek() {
    if (top == -1)
        return '\0';
    return stack[top];
}


int precedence(char op) {
    switch(op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}


int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char *infix, char *postfix) {
    int i, j = 0;
    char ch;
    
    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];
        
        if (isalpha(ch) || isdigit(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (peek() != '(' && top != -1) {
                postfix[j++] = pop();
            }
            pop(); // remove '(' from stack
        } else if (isOperator(ch)) {
            while (isOperator(peek()) && 
                   ((precedence(ch) < precedence(peek())) || 
                   (precedence(ch) == precedence(peek()) && ch != '^'))) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }
     
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}
int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}

