/*Write an OpenMP program where a parallel region is created and each thread prints: 
"Hello from thread <thread_id> out of <total_threads> threads". */


#include <stdio.h>
#include <omp.h>

int main() {
    
    //number of threads
    int th;  
    printf("Enter the number of threads:\n");
    scanf("%d", &th);

    // Set the number of threads for parallel 
    omp_set_num_threads(th);

    // Start parallel 
    #pragma omp parallel
    {
        printf("Hello from thread %d out of %d threads\n",
               omp_get_thread_num(),
               omp_get_num_threads());
    }

    // Program ends
    return 0;
}



// To compile: gcc 1.c -fopenmp -o 1
// To run: ./1

/*
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 1.c -fopenmp -o 1
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./1
Enter the number of Threads:
4
Hello from thread 2 out of 4 threads
Hello from thread 3 out of 4 threads
Hello from thread 0 out of 4 threads
Hello from thread 1 out of 4 threads
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./1
Enter the no of Threads:
6
Hello from thread 5 out of 6 threads
Hello from thread 2 out of 6 threads
Hello from thread 3 out of 6 threads
Hello from thread 4 out of 6 threads
Hello from thread 0 out of 6 threads
Hello from thread 1 out of 6 threads
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$
*/