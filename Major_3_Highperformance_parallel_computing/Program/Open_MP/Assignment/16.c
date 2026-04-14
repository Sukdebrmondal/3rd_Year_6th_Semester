/*Write an OpenMP program using #pragma omp task to compute Fibonacci numbers 
recursively. Create tasks for recursive calls. */

#include<stdio.h>
#include<omp.h>

int fib(int n){

    if(n<=1)
        return n;

    int x,y;

#pragma omp task shared(x)
    x = fib(n-1);

#pragma omp task shared(y)
    y = fib(n-2);

#pragma omp taskwait

    return x+y;
}

int main(){

    int n = 15;
    int result;

#pragma omp parallel
    {
#pragma omp single
        result = fib(n);
    }

    printf("The Fibonacci(%d) numbers = %d\n",n,result);

    return 0;
}

// To compile: gcc 16.c -fopenmp -o 16
// To run: ./16


/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 16.c -fopenmp -o 16
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./16
The Fibonacci(10) numbers = 55


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 16.c -fopenmp -o 16
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./16
The Fibonacci(15) numbers = 610


*/