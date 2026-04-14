// 5. Write an OpenMP program to add two matrices of size N × N. Parallelize the outer loop.

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main(){

    int size;
    srand(time(NULL));
    printf("Enter the size of the N x N matrix: \n");
    scanf("%d",&size);

    int A[size][size];
    int B[size][size];
    int res[size][size];


    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            A[i][j] = rand()%100;
            B[i][j] = rand()%100;
        }
    }


    //  matrix A
    printf("\nThis is Matrix A:\n");
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }
    //  matrix B
    printf("\nThis is Matrix B:\n");
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            printf("%3d ",B[i][j]);
        }
        printf("\n");
    }

    #pragma omp parallel for
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            res[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nThis is result matrix:\n");
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            printf("%3d ",res[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// gcc 5.c -fopenmp -o 5

/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 5.c -fopenmp -o 5
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./5
Enter the size of the N x N matrix:
2

This is Matrix A:
 10  40
 56  14

This is Matrix B:
 76  38
 31  24

This is result matrix:
 86  78
 87  38



 sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 5.c -fopenmp -o 5
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./5
Enter the size of the N x N matrix:
3

This is Matrix A:
 52  93  93
 20  54  33
 82  55  45

This is Matrix B:
  1  56  18
 54  28   2
 36   4  60

This is result matrix:
 53 149 111
 74  82  35
118  59 105





*/