/*Write an MPI program where process 0 creates an integer array of size N. Use 
MPI_Scatter to distribute equal chunks of the array to all processes. Each process 
multiplies every element of its chunk by 2. Use MPI_Gather to collect the modified 
chunks back into process 0. Process 0 prints the final modified array. */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int N;

    int *arr = NULL;       // Full array (only in process 0)
    int *local_arr;        // Local chunk

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Input (only process 0)
    if (rank == 0) {
        printf("Enter size of array (N):\n");
        scanf("%d", &N);

        arr = (int*)malloc(N * sizeof(int));

        printf("Enter %d elements:\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        printf("\n");
    }

    //Send N to all processes
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Calculate chunk size
    int chunk = N / size;
    int remainder = N % size;

    //Allocate memory for local chunk
    local_arr = (int*)malloc(chunk * sizeof(int));

    //Scatter data
    MPI_Scatter(arr, chunk, MPI_INT,
                local_arr, chunk, MPI_INT,
                0, MPI_COMM_WORLD);

    //Multiply each element by 2
    for (int i = 0; i < chunk; i++) {
        local_arr[i] *= 2;
    }

    //Gather data back to process 0
    MPI_Gather(local_arr, chunk, MPI_INT,
               arr, chunk, MPI_INT,
               0, MPI_COMM_WORLD);

    //Handle leftover elements (only process 0)
    if (rank == 0) {
        for (int i = chunk * size; i < N; i++) {
            arr[i] *= 2;
        }

        //Print final result
        printf("Modified array:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}


// mpicc 4.c -o 4 && mpirun -np 6 ./4

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 4.c -o 4 && mpirun -np 4 ./4
Enter size of array (N):
7
Enter 7 elements:
1 2 3 4 5 6 7

Modified array:
2 4 6 8 10 12 14
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 4.c -o 4 && mpirun -np 6 ./4
Enter size of array (N):
5
Enter 5 elements:
32 12 45 64 23

Modified array:
64 24 90 128 46
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$
*/