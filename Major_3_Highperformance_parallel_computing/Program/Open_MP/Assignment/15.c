/*Write an OpenMP program where a parallel region contains another parallel region. Enable 
nested parallelism using omp_set_nested(1). Print thread IDs at both levels. Explain how 
nested parallelism behaves.*/

#include<stdio.h>
#include<omp.h>

int main(){
    omp_set_num_threads(4);

    omp_set_nested(1);
    #pragma omp parallel
    {
        int outer_id = omp_get_thread_num();
        printf("outer thread %d\n",outer_id);

    #pragma omp parallel
    {
        int inner_id = omp_get_thread_num();
        printf("Inner thread %d outer thread %d\n",inner_id,outer_id);
    }
        }
    return 0;
}

// To compile: gcc 15.c -fopenmp -o 15
// To run: ./15


/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 15.c -fopenmp -o 15
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./15
outer thread 0
outer thread 1
Inner thread 0 outer thread 0
Inner thread 1 outer thread 0
Inner thread 0 outer thread 1
Inner thread 1 outer thread 1




sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 15.c -fopenmp -o 15
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./15
outer thread 0
outer thread 2
outer thread 1
outer thread 3
Inner thread 1 outer thread 0
Inner thread 0 outer thread 0
Inner thread 3 outer thread 0
Inner thread 2 outer thread 0
Inner thread 1 outer thread 3
Inner thread 2 outer thread 3
Inner thread 0 outer thread 3
Inner thread 3 outer thread 3
Inner thread 2 outer thread 2
Inner thread 3 outer thread 2
Inner thread 1 outer thread 2
Inner thread 0 outer thread 2
Inner thread 2 outer thread 1
Inner thread 0 outer thread 1
Inner thread 3 outer thread 1
Inner thread 1 outer thread 1

*/