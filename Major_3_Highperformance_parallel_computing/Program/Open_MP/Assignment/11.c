/*Write an OpenMP program to compute the prefix sum of an array.
Example: Input: [1,2,3,4], Output: [1,3,6,10]*/

#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#define N 10

int main(){
    int arr[N];
    int arr_2[N];
    int sum = 0;
    srand(time(NULL));

    for(int i = 0;i<N;i++){
        arr[i] = rand()%10;
    }
    for(int i = 0;i<N;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0;i<N;i++){
        sum = 0;
        for(int j = 0;j<=i;j++){
            sum+=arr[j];
        }
        arr_2[i] = sum;
    }
    for(int i = 0;i<N;i++){
        printf("The prefix sum of an array:%d\n",arr_2[i]);
    }
}

// To compile: gcc 11.c -fopenmp -o 11
// To run: ./11

/*
b@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 11.c -fopenmp -o 11
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./11
0 1 1 9 5 8 5 6 8 0
The prefix sum of an array:0
The prefix sum of an array:1
The prefix sum of an array:2
The prefix sum of an array:11
The prefix sum of an array:16
The prefix sum of an array:24
The prefix sum of an array:29
The prefix sum of an array:35
The prefix sum of an array:43
The prefix sum of an array:43




sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 11.c -fopenmp -o 11
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./11
2 5 3 8 5 6 7 8 7 0
The prefix sum of an array:2
The prefix sum of an array:7
The prefix sum of an array:10
The prefix sum of an array:18
The prefix sum of an array:23
The prefix sum of an array:29
The prefix sum of an array:36
The prefix sum of an array:44
The prefix sum of an array:51
The prefix sum of an array:51


*/