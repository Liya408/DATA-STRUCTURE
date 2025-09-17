#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char opStack[MAX];  // Operator stack
int top = -1;

void push(char x) {
    opStack[++top] = x;
}

char pop() {
    if (top == -1)
        return -1;
    else
        return opStack[top--];
}

char peek() {
    if (top == -1)
        return -1;
    return opStack[top];
}

int precedence(char x) {
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return 0;
}

int isNumericExpr(const char* expr) {
    while (*expr) {
        if (isalpha(*expr)) return 0;  // If contains variable, not numeric
        expr++;
    }
    return 1;
}

// Evaluate postfix expression assuming all values are integers
int evaluatePostfix(const char* postfix) {
    int valStack[MAX];
    int top = -1;
    int i = 0;

    while (postfix[i]) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            valStack[++top] = num;
        } else if (postfix[i] == ' ') {
            i++;
        } else {
            int b = valStack[top--];
            int a = valStack[top--];
            int result;
            switch (postfix[i]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: result = 0;
            }
            valStack[++top] = result;
            i++;
        }
    }

    return valStack[top];
}

int main() {
    char infix[MAX], postfix[MAX] = "";
    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);

    int i = 0, j = 0;
    char token;
    int numeric = isNumericExpr(infix);

    while (infix[i] != '\0' && infix[i] != '\n') {
        token = infix[i];

        if (isspace(token)) {
            i++;
            continue;
        }

        if (isdigit(token)) {
            // Append full number to postfix
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        } else if (isalpha(token)) {
            postfix[j++] = token;
            postfix[j++] = ' ';
        } else if (token == '(') {
            push(token);
        } else if (token == ')') {
            while (peek() != '(') {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            pop(); // pop '('
        } else { // operator
            while (top != -1 && precedence(peek()) >= precedence(token)) {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            push(token);
        }

        i++;
    }

    while (top != -1) {
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';

    printf("\nPostfix expression: %s\n", postfix);

    if (numeric) {
        int result = evaluatePostfix(postfix);
        printf("Evaluated result: %d\n", result);
    } else {
        printf("Expression contains variables. Skipping evaluation.\n");
    }

    return 0;
}
