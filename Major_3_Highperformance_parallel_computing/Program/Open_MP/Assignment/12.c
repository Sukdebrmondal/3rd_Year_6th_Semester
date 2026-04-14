/*Write an OpenMP program where an array of random numbers (0–9) is generated and
compute frequency of each number in parallel.*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>


int main(){
    srand(time(NULL));
    int n;
    printf("Enter the number of elements in the array:\n");
    scanf("%d",&n);

    int occr[10] = {0};

    int a[n];
    for(int i = 0;i<n;i++){
        a[i] = rand()%10;
    }

    printf("The unsorted array is\n");
    for(int i = 0;i<n;i++){
        printf("%2d ",a[i]);
    }
    printf("\n");
    #pragma omp parallel for
    for(int i = 0;i<n;i++){
        #pragma omp atomic
        occr[a[i]]++;
    }

    for(int i = 0;i<10;i++){
        if(occr[i]!=0){
            printf("The occurance of %d is %d\n",i,occr[i]);
        }
    }
}

// To compile: gcc 12.c -fopenmp -o 12
// To run: ./12

/*

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 12.c -fopenmp -o 12
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./12
Enter the number of elements in the array:
4
The unsorted array is
 0  6  6  8
The occurance of 0 is 1
The occurance of 6 is 2
The occurance of 8 is 1


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 12.c -fopenmp -o 12
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./12
Enter the number of elements in the array:
7
The unsorted array is
 8  9  0  0  2  5  1
The occurance of 0 is 2
The occurance of 1 is 1
The occurance of 2 is 1
The occurance of 5 is 1
The occurance of 8 is 1
The occurance of 9 is 1











*/