#include <stdio.h>

#define MAX 100

typedef struct {
    int row;
    int col;
    int value;
} Element;

void inputMatrix(int matrix[MAX][MAX], int rows, int cols) {
    printf("Enter matrix elements (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
}

void createSparse(int matrix[MAX][MAX], int rows, int cols, Element compact[MAX], int *size) {
    int k = 1; // Index 0 for meta info
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (matrix[i][j] != 0) {
                compact[k].row = i;
                compact[k].col = j;
                compact[k].value = matrix[i][j];
                k++;
            }
    compact[0].row = rows;
    compact[0].col = cols;
    compact[0].value = k - 1; // Number of non-zero elements
    *size = k;
}

void printMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");
    }
}

void printCompact(Element compact[MAX], int size) {
    printf("Row Col Val\n");
    for (int i = 0; i < size; i++)
        printf("%3d %3d %3d\n", compact[i].row, compact[i].col, compact[i].value);
}

void sumSparse(Element a[MAX], int sizeA, Element b[MAX], int sizeB, Element result[MAX], int *sizeR) {
    int i = 1, j = 1, k = 1;
    // Meta info for result: rows and cols same as inputs
    result[0].row = a[0].row;
    result[0].col = a[0].col;

    while (i < sizeA && j < sizeB) {
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            int summedValue = a[i].value + b[j].value;
            if (summedValue != 0) {
                result[k].row = a[i].row;
                result[k].col = a[i].col;
                result[k].value = summedValue;
                k++;
            }
            i++; j++;
        }
        else if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            result[k++] = a[i++];
        } else {
            result[k++] = b[j++];
        }
    }
    while (i < sizeA) result[k++] = a[i++];
    while (j < sizeB) result[k++] = b[j++];

    result[0].value = k - 1;
    *sizeR = k;
}

void compactToMatrix(Element compact[MAX], int size, int matrix[MAX][MAX]) {
    int rows = compact[0].row;
    int cols = compact[0].col;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = 0;

    for (int i = 1; i < size; i++)
        matrix[compact[i].row][compact[i].col] = compact[i].value;
}

void transpose(Element src[MAX], Element trans[MAX], int size) {
    trans[0].row = src[0].col;
    trans[0].col = src[0].row;
    trans[0].value = src[0].value;

    int k = 1;
    for (int c = 0; c < src[0].col; c++) {
        for (int i = 1; i < size; i++) {
            if (src[i].col == c) {
                trans[k].row = src[i].col;
                trans[k].col = src[i].row;
                trans[k].value = src[i].value;
                k++;
            }
        }
    }
}

int main() {
    int rows, cols;

    printf("Enter number of rows and columns for matrices: ");
    scanf("%d %d", &rows, &cols);

    int mat1[MAX][MAX], mat2[MAX][MAX];

    // Input matrices
    printf("Matrix 1:\n");
    inputMatrix(mat1, rows, cols);

    printf("Matrix 2:\n");
    inputMatrix(mat2, rows, cols);

    // Convert to compact form
    Element comp1[MAX], comp2[MAX], sumComp[MAX], transComp[MAX];
    int size1, size2, sizeSum, sizeTrans;

    createSparse(mat1, rows, cols, comp1, &size1);
    createSparse(mat2, rows, cols, comp2, &size2);

    // Sum in compact form
    sumSparse(comp1, size1, comp2, size2, sumComp, &sizeSum);

    // Convert sum to normal matrix
    int sumMat[MAX][MAX];
    compactToMatrix(sumComp, sizeSum, sumMat);

    // Transpose the sum (compact form)
    transpose(sumComp, transComp, sizeSum);

    // Convert transpose to matrix
    int transMat[MAX][MAX];
    compactToMatrix(transComp, sizeSum, transMat);

    // Display all
    printf("\nMatrix 1:\n");
    printMatrix(mat1, rows, cols);

    printf("\nMatrix 2:\n");
    printMatrix(mat2, rows, cols);

    printf("\nCompact form of Matrix 1:\n");
    printCompact(comp1, size1);

    printf("\nCompact form of Matrix 2:\n");
    printCompact(comp2, size2);

    printf("\nSum (compact form):\n");
    printCompact(sumComp, sizeSum);

    printf("\nSum (matrix form):\n");
    printMatrix(sumMat, rows, cols);

    printf("\nTranspose of Sum (compact form):\n");
    printCompact(transComp, sizeSum);

    printf("\nTranspose of Sum (matrix form):\n");
    printMatrix(transMat, cols, rows); // transpose dims swapped

    return 0;
}

