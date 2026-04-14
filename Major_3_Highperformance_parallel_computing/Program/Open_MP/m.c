#include <stdio.h>
#include <omp.h>

#define N 4

// Function to print a matrix
void printMatrix(int M[N][N], const char *name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j;
        }
    }
 // Print input matrices
    printMatrix(A, "Input Matrix A:");
    printMatrix(B, "Input Matrix B:");

    // Parallel matrix addition
    #pragma omp parallel for collapse(2) //Normally, OpenMP parallelizes only the outer loop. collapse(2) combines the
                                         //two loops into one loop of total iterations.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j]; //No race condition happens as multiple threads do not write to the same memory
                                         //location.
        }
    }

    // Print output matrix
    printMatrix(C, "Output Matrix C:");

    return 0;
}