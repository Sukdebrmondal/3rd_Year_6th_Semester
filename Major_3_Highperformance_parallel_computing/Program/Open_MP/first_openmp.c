#include <stdio.h>
#include <omp.h>

int main() {


    omp_set_num_threads(4); //Controls number of threads

    #pragma omp parallel //Creates a parallel region, Multiple threads execute the block
    {
        printf("Hello from thread %d\n", omp_get_thread_num()); //omp_get_thread_num() returns thread ID
    }

    return 0;
}


// To compile: gcc first_openmp.c -fopenmp -o first_openmp
// To run: ./first_openmp