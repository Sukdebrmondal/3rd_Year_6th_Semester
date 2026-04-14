/*Write an OpenMP program to compute the sum of an integer array using #pragma omp 
parallel for. Don’t use reduction initially. Observe incorrect results due to race conditions. 
Fix the problem using #pragma omp critical. Modify this program using reduction. Compare 
execution time with the critical version. */


#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main(){
    srand(time(NULL));
    int r_sum = 0,sum=0;
    int n = 20;
    double start,end;

    int arr[n];
    for(int i=0;i<n;i++){
        arr[i] = rand()%100;
        r_sum+=arr[i];
    }

    printf("\nThe initial array:\n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    printf("The sum of this original array is: %d\n",r_sum);


    sum = 0;
    printf("\nsum of array using #pragma omp for...\nthat might cause race condition");
    start = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    end = omp_get_wtime();
    printf("\nsum of this array is: %d\n",sum);
    printf("execution time: %f\n",end-start);
    
    
    sum = 0;
    printf("\nsum of array using #pragma omp for and critical");
    start = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        #pragma omp critical
        sum+=arr[i];
    }
    end = omp_get_wtime();
    printf("\nsum of this array is: %d\n",sum);
    printf("execution time: %f\n",end-start);
    
    
    sum = 0;
    printf("\nsum calculation using #pragma omp for reduction");
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    end = omp_get_wtime();
    printf("\nsum of this array is: %d\n",sum);
    printf("execution time: %f\n",end-start);
}


// To compile: gcc 3.c -fopenmp -o 3
// To run: ./3

/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 3.c -fopenmp -o 3
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./3

The initial array:
97 11 47 50 69 94 98 62 12 50 97 90 94 60 68 52 89 27 20 43
The sum of this original array is: 1230

sum of array using #pragma omp for...
that might cause race condition
sum of this array is: 1076
execution time: 0.002840

sum of array using #pragma omp for and critical
sum of this array is: 1230
execution time: 0.001204

sum calculation using #pragma omp for reduction
sum of this array is: 1230
execution time: 0.001218


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 3.c -fopenmp -o 3
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./3

The initial array:
68 78 0 16 28 50 10 32 83 24 77 1 80 60 85 93 18 3 61 65
The sum of this original array is: 932

sum of array using #pragma omp for...
that might cause race condition
sum of this array is: 932
execution time: 0.007716

sum of array using #pragma omp for and critical
sum of this array is: 932
execution time: 0.008098

sum calculation using #pragma omp for reduction
sum of this array is: 932
execution time: 0.007539


*/