#include <stdio.h>

#define MAX_TERMS 10

struct Term {
    int coeff;
    int expo;
};

int main() {
    struct Term p1[MAX_TERMS], p2[MAX_TERMS], result[MAX_TERMS];
    int n1, n2, i, j, k;

    // Input first polynomial
    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n1);
    printf("Enter terms (coefficient and exponent) in descending order of exponent:\n");
    for (i = 0; i < n1; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &p1[i].coeff, &p1[i].expo);
    }

    // Input second polynomial
    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n2);
    printf("Enter terms (coefficient and exponent) in descending order of exponent:\n");
    for (i = 0; i < n2; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &p2[i].coeff, &p2[i].expo);
    }

    // Initialize result polynomial
    k = 0;
    i = 0;
    j = 0;

    // Add the polynomials
    while (i < n1 && j < n2) {
        if (p1[i].expo == p2[j].expo) {
            result[k].coeff = p1[i].coeff + p2[j].coeff;
            result[k].expo = p1[i].expo;
            i++;
            j++;
        } else if (p1[i].expo > p2[j].expo) {
            result[k] = p1[i];
            i++;
        } else {
            result[k] = p2[j];
            j++;
        }
        k++;
    }

    // Copy remaining terms
    while (i < n1) {
        result[k] = p1[i];
        i++;
         k++;
    }
    while (j < n2) {
        result[k] = p2[j];
        j++;
        k++;
    }

    // Output the result
    printf("\n Sum of the polynomials: ");
    for (i = 0; i < k; i++) {
        if (i > 0 && result[i].coeff > 0)
            printf(" + ");
        printf("%dx^%d", result[i].coeff, result[i].expo);
    }
    printf("\n");

    return 0;
}

