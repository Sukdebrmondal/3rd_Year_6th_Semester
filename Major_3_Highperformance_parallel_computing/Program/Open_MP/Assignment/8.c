/*Write an OpenMP program that uses multiple threads. One thread produces numbers. Other 
threads consume numbers. Use synchronization constructs #pragma omp critical and 
#pragma omp atomic. Demonstrate proper synchronization to avoid data corruption. */

#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#define N 5

int main(){
    int array[N];
    int count = 0;
    srand(time(NULL));

    #pragma omp parallel shared(array, count)
    { 
        if(omp_get_thread_num() == 0){
            for(int i = 0;i<N;i++){
                #pragma omp critical
                {
                    if (count < N){
                        array[count] = rand()%100;
                        int value = array[count] ;
                        #pragma omp atomic
                        count++;
                        printf("producer produced %d (count = %d)\n", value, count);
                    }
                }
            }
        }
        else{

            for(int i = 0;i<N;i++){
                #pragma omp critical
                {
                    if (count > 0){
                    int value = array[count-1] ;
                    #pragma omp atomic
                    count--;
                    printf("consumer consumed %d (count = %d)\n", value, count);
                    }
                }
            }
        }
    }
}

// To compile: gcc 8.c -fopenmp -o 8
// To run: ./8

/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 8.c -fopenmp -o 8
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./8
producer produced 83 (count = 1)
producer produced 7 (count = 2)
producer produced 20 (count = 3)
producer produced 29 (count = 4)
producer produced 11 (count = 5)


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 8.c -fopenmp -o 8
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./8
producer produced 45 (count = 1)
producer produced 47 (count = 2)
producer produced 87 (count = 3)
producer produced 87 (count = 4)
producer produced 84 (count = 5)




*/