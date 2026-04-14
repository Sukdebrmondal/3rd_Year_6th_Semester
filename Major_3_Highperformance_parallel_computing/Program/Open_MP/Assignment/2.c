/*Write an OpenMP program to print numbers from 1 to N. Use #pragma omp parallel for to    
distribute iterations among threads. Each thread should print the number it is processing  
and its thread ID. */


#include <stdio.h>
#include <omp.h>
int main() {

    int x;  
    printf("Enter the number: \n");
    scanf("%d", &x);

    // Parallel for loop
    #pragma omp parallel for
    for (int i = 1; i <= x; i++) {
        printf("Thread %d is processing number %d\n",
               omp_get_thread_num(), i);
    }

    return 0;  
}



// To compile: gcc 2.c -fopenmp -o 2
// To run: ./2

/*
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 2.c -fopenmp -o 2
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./2
Enter the number:
4
Thread 2 is processing number 3
Thread 0 is processing number 1
Thread 1 is processing number 2
Thread 3 is processing number 4
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./2
Enter the number:
6
Thread 0 is processing number 1
Thread 5 is processing number 6
Thread 1 is processing number 2
Thread 4 is processing number 5
Thread 2 is processing number 3
Thread 3 is processing number 4
*/