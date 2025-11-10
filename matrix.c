#include <stdio.h>
#define MAX 10

// Function to read a matrix
void readMatrix(int mat[MAX][MAX], int row, int col, int num) {
    printf("\nEnter elements of Matrix %d (%d x %d):\n", num, row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &mat[i][j]);
        }
    }
}

// Function to print a matrix
void printMatrix(int mat[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

// Function to add two matrices
void addTwoMatrices(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Function to multiply two matrices
void multiplyTwoMatrices(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++)
                result[i][j] += A[i][k] * B[k][j];
        }
    }
}

// Function for transpose
void transposeMatrix(int A[MAX][MAX], int result[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            result[j][i] = A[i][j];
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], result[MAX][MAX], temp[MAX][MAX];
    int r1, c1, r2, c2, choice, n;

    do {
        printf("\n========== MATRIX OPERATIONS ==========\n");
        printf("1. Matrix Addition (any number)\n");
        printf("2. Matrix Multiplication (any number)\n");
        printf("3. Matrix Transpose\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            // Matrix Addition
            case 1:
                printf("\n--- MATRIX ADDITION ---\n");
                printf("Enter number of matrices to add: ");
                scanf("%d", &n);

                if (n < 2) {
                    printf("You need at least 2 matrices for addition!\n");
                    break;
                }

                printf("Enter number of rows and columns: ");
                scanf("%d%d", &r1, &c1);

                readMatrix(temp, r1, c1, 1);  // first matrix

                for (int m = 2; m <= n; m++) {
                    readMatrix(A, r1, c1, m);
                    addTwoMatrices(temp, A, result, r1, c1);

                    // copy result to temp for next addition
                    for (int i = 0; i < r1; i++)
                        for (int j = 0; j < c1; j++)
                            temp[i][j] = result[i][j];
                }

                printf("\nFinal Result after adding %d matrices:\n", n);
                printMatrix(result, r1, c1);
                break;

            // Matrix Multiplication
            case 2:
                printf("\n--- MATRIX MULTIPLICATION ---\n");
                printf("Enter number of matrices to multiply: ");
                scanf("%d", &n);

                if (n < 2) {
                    printf("You need at least 2 matrices for multiplication!\n");
                    break;
                }

                printf("\nEnter rows and columns of Matrix 1: ");
                scanf("%d%d", &r1, &c1);
                readMatrix(temp, r1, c1, 1);

                int currRows = r1, currCols = c1;

                for (int m = 2; m <= n; m++) {
                    printf("\nEnter rows and columns of Matrix %d: ", m);
                    scanf("%d%d", &r2, &c2);

                    if (currCols != r2) {
                        printf("\nError: Multiplication not possible! (Columns of previous matrix must equal Rows of next matrix)\n");
                        break;
                    }

                    readMatrix(B, r2, c2, m);

                    multiplyTwoMatrices(temp, B, result, currRows, currCols, c2);

                    // Copy result into temp for next multiplication
                    for (int i = 0; i < currRows; i++)
                        for (int j = 0; j < c2; j++)
                            temp[i][j] = result[i][j];

                    currCols = c2; // update new column count
                }

                printf("\nFinal Result after multiplying %d matrices:\n", n);
                printMatrix(result, currRows, currCols);
                break;

            // Matrix Transpose
            case 3:
                printf("\n--- MATRIX TRANSPOSE ---\n");
                printf("Enter number of matrices to transpose: ");
                scanf("%d", &n);

                for (int m = 1; m <= n; m++) {
                    printf("\nEnter number of rows and columns of Matrix %d: ", m);
                    scanf("%d%d", &r1, &c1);

                    readMatrix(A, r1, c1, m);

                    transposeMatrix(A, result, r1, c1);

                    printf("\nTranspose of Matrix %d:\n", m);
                    printMatrix(result, c1, r1);
                }
                break;

            // Exit
            case 4:
                printf("\nProgram exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}
