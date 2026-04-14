/*Write an OpenMP program where a global variable counter is declared. Inside a parallel
region, each thread modifies counter. First run without any clause and observe incorrect
behaviour. Then use private(counter) and compare results. Explain the difference between
shared and private variables. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int count = 0;

int main(){

    // int count = 0;
    printf("case 1(without using any clause)\n");
    printf("at first count is %d\n",count);
    count+=1;
    printf("after increment count is %d\n",count);
    
    count = 0;
    printf("\n\ncase 2(using only palallel)\n");
    printf("at first count is %d\n",count);
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        count+=1;
        printf("value of count inside the thread %d\n",count);
    }
    printf("after increment count is %d\n",count);

    count = 0;
    printf("\n\ncase 3(using palallel private(count)\n");
    printf("at first count is %d\n",count);
    omp_set_num_threads(4);
    #pragma omp parallel private(count)
    {
        count+=1;
        printf("value of count inside the thread %d\n",count);
    }
    printf("after increment count is %d\n",count);

}

// To compile: gcc 9.c -fopenmp -o 9
// To run: ./9

/*
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 9.c -fopenmp -o 9
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./9
case 1(without using any clause)
at first count is 0
after increment count is 1


case 2(using only palallel)
at first count is 0
value of count inside the thread 1
value of count inside the thread 1
value of count inside the thread 1
value of count inside the thread 2
after increment count is 2


case 3(using palallel private(count)
at first count is 0
value of count inside the thread 1
value of count inside the thread 1
value of count inside the thread 1
value of count inside the thread 30216
after increment count is 0


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 9.c -fopenmp -o 9
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./9
case 1(without using any clause)
at first count is 0
after increment count is 1


case 2(using only palallel)
at first count is 0
value of count inside the thread 1
value of count inside the thread 2
value of count inside the thread 3
value of count inside the thread 4
after increment count is 4


case 3(using palallel private(count)
at first count is 0
value of count inside the thread 1
value of count inside the thread 1
value of count inside the thread 1
value of count inside the thread 31006
after increment count is 0

*/