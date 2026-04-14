/*Write an OpenMP program to generate an array of random integers. Find the maximum 
element using reduction. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main(){
    srand(time(NULL));

    int arr[10];

    printf("The initial array is:\n");
    for(int i = 0;i<10;i++){
        arr[i] = rand()%100;
    }

    int max = 0;

    for(int i = 0;i<10;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    #pragma omp parallel for reduction(max:max)
    for(int i = 0;i<10;i++){
        if (max < arr[i]){
            max = arr[i];
        }
    }

    printf("The maximum element using reduction: %d \n",max);

}

// To compile: gcc 4.c -fopenmp -o 4
// To run: ./4


/*
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 4.c -fopenmp -o 4
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./4
The initial array is:
81 5 55 11 99 57 22 81 1 1
The maximum element using reduction: 99


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 4.c -fopenmp -o 4
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./4
The initial array is:
79 58 17 7 85 20 83 72 9 88
The maximum element using reduction: 88


*/