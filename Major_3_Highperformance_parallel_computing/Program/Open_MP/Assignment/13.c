/*Write an OpenMP program to sort an array using odd-even transposition sort. Parallelize comparison phases.*/

//Parallel Odd-Even Sort using OpenMP
#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#include<time.h>

int main() {
    srand(time(NULL));
    int n;
    printf("Enter the number of elements in the array:\n");
    scanf("%d",&n);
    int a[n];
    for(int i = 0;i<n;i++){
        a[i] = rand()%100;
    }

    printf("the unsorted array is\n");
    for(int i = 0;i<n;i++){
        printf("%3d ",a[i]);
    }

    for (int phase = 0; phase < n; phase++) {

        if (phase % 2 == 0) {
            #pragma omp parallel for
            for (int i = 1; i < n; i += 2) {
                if (a[i-1] > a[i]) {
                    int temp = a[i];
                    a[i] = a[i-1];
                    a[i-1] = temp;
                }
            }
        } else {
            #pragma omp parallel for
            for (int i = 1; i < n-1; i += 2) {
                if (a[i] > a[i+1]) {
                    int temp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = temp;
                }
            }
        }
    }

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%3d ", a[i]);
    printf("\n");
    return 0;
}

// To compile: gcc 13.c -fopenmp -o 13
// To run: ./13




/*


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 13.c -fopenmp -o 13
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./13
Enter the number of elements in the array:
4
the unsorted array is
 29  80  38   9
Sorted array:
  9  29  38  80
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 13.c -fopenmp -o 13
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./13
Enter the number of elements in the array:
7
the unsorted array is
 40   9  51  92  13  76  19
Sorted array:
  9  13  19  40  51  76  92



*/