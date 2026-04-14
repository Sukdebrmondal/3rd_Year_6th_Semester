/*Write an OpenMP program to multiply two N × N matrices. Use #pragma omp parallel for 
on outer loop. Compare performance for different thread counts.*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

int main(){

    int size;
    srand(time(NULL));
    printf("Enter the size of the N x N matrix: \n");
    scanf("%d",&size);

    int A[size][size];
    int B[size][size];
    int res[size][size];
    double start,end;

    int max_thread = 10;

    for(int t = 1;t<=max_thread;t++){

        omp_set_num_threads(t);

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

        start = omp_get_wtime();
        
        #pragma omp parallel for
        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++){
                int sum = 0;
                for(int k =0;k<size;k++){
                    sum += A[i][k] * B[k][j];
                }
                res[i][j] = sum;
            }
        }

        end = omp_get_wtime();

        printf("\nThis is result matrix:\n");
        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++){
                printf("%3d ",res[i][j]);
            }
            printf("\n");
        }
        printf("\nThreads used: %d\n",t);
        printf("Execution time: %f seconds\n", end - start);
    }

    return 0;
}

// To compile: gcc 6.c -fopenmp -o 6
// To run: ./6


/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 6.c -fopenmp -o 6
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./6
Enter the size of the N x N matrix:
2

This is Matrix A:
 89  24
 38  17

This is Matrix B:
 57  20
 65  93

This is result matrix:
6633 4012
3271 2341

Threads used: 1
Execution time: 0.000032 seconds

This is Matrix A:
 29  85
  3  82

This is Matrix B:
 95  14
 42  46

This is result matrix:
6325 4316
3729 3814

Threads used: 2
Execution time: 0.000377 seconds

This is Matrix A:
 49  97
 52  57

This is Matrix B:
 75  31
 93  16

This is result matrix:
12696 3071
9201 2524

Threads used: 3
Execution time: 0.000224 seconds

This is Matrix A:
 66  65
 30  45

This is Matrix B:
 23  52
 89  19

This is result matrix:
7303 4667
4695 2415

Threads used: 4
Execution time: 0.000894 seconds

This is Matrix A:
 98  91
 38  81

This is Matrix B:
 21  88
  8  67

This is result matrix:
2786 14721
1446 8771

Threads used: 5
Execution time: 0.000362 seconds

This is Matrix A:
 55  81
 61  57

This is Matrix B:
 19  59
 15  63

This is result matrix:
2260 8348
2014 7190

Threads used: 6
Execution time: 0.000699 seconds

This is Matrix A:
 43  94
 99  11

This is Matrix B:
 54  95
 51  17

This is result matrix:
7116 5683
5907 9592

Threads used: 7
Execution time: 0.001469 seconds

This is Matrix A:
 26  21
 69  27

This is Matrix B:
 28   8
 66  67

This is result matrix:
2114 1615
3714 2361

Threads used: 8
Execution time: 0.001117 seconds

This is Matrix A:
 87   7
 30  44

This is Matrix B:
 70  77
 88  86

This is result matrix:
6706 7301
5972 6094

Threads used: 9
Execution time: 0.000800 seconds

This is Matrix A:
 59  45
 45  36

This is Matrix B:
 78  21
  2  88

This is result matrix:
4692 5199
3582 4113

Threads used: 10
Execution time: 0.001129 seconds



sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 6.c -fopenmp -o 6
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./6
Enter the size of the N x N matrix:
3

This is Matrix A:
 52  80  81
 10  48   5
 10  61  69

This is Matrix B:
 93  61  90
 55  90  62
 54   0  93

This is result matrix:
13610 10372 17173
3840 4930 4341
8011 6100 11099

Threads used: 1
Execution time: 0.000034 seconds

This is Matrix A:
  6  14  85
 13  25  67
 12  39  84

This is Matrix B:
 58  22  96
  2  17  46
 71  44  72

This is result matrix:
6411 4110 7340
5561 3659 7222
6738 4623 8994

Threads used: 2
Execution time: 0.000625 seconds

This is Matrix A:
 34  27  37
 96  91   0
  2  22  80

This is Matrix B:
 47  34  84
 47   9  12
 58  68   7

This is result matrix:
5013 3915 3439
8789 4083 9156
5768 5706 992

Threads used: 3
Execution time: 0.000496 seconds

This is Matrix A:
 17  61  63
 88  52  71
  4  84  92

This is Matrix B:
 93  42  81
 27  80  37
 58  84  73

This is result matrix:
6882 10886 8233
13706 13820 14235
7976 14616 10148

Threads used: 4
Execution time: 0.000265 seconds

This is Matrix A:
 20  73  98
 23  83  73
  5  61  84

This is Matrix B:
 89  11  25
 53  45  15
 90  18  76

This is result matrix:
14469 5269 9043
13016 5302 7368
11238 4312 7424

Threads used: 5
Execution time: 0.000236 seconds

This is Matrix A:
 51   3  57
 93  32  97
 54  66  81

This is Matrix B:
 25   4  74
 61  29  77
 18  27  16

This is result matrix:
2484 1830 4917
6023 3919 10898
6834 4317 10374

Threads used: 6
Execution time: 0.000295 seconds

This is Matrix A:
 52  21   2
  3  85  30
 40  47  37

This is Matrix B:
 57  87  95
 59  64  70
 81  95   4

This is result matrix:
4365 6058 6418
7616 8551 6355
8050 10003 7238

Threads used: 7
Execution time: 0.001129 seconds

This is Matrix A:
 69  65  63
 31  33  45
 17  23  37

This is Matrix B:
 82  54  15
 18  49  14
 50  39  78

This is result matrix:
9978 9368 6859
5386 5046 4437
3658 3488 3463

Threads used: 8
Execution time: 0.000835 seconds

This is Matrix A:
 34  37  56
 93  53  43
 44  25  19

This is Matrix B:
 40  71  19
 96  40  42
 65  62  40

This is result matrix:
8552 7366 4440
11603 11389 5713
5395 5302 2646

Threads used: 9
Execution time: 0.001559 seconds

This is Matrix A:
 77  58   3
 28   6  11
 30  36  69

This is Matrix B:
  2  62  56
 20  52  43
 45  19  92

This is result matrix:
1449 7847 7082
671 2257 2838
3885 5043 9576

Threads used: 10
Execution time: 0.001243 seconds



*/