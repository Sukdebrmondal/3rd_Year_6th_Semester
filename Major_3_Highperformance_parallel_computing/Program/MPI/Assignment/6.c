/* Write an MPI program where each process generates M random integers, each process 
finds the maximum number in its local list. Use MPI_Reduce to find the global 
maximum among all processes. Process 0 prints the global maximum. */


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int M;                 // number of random numbers
    int local_max = -1;
    int global_max;

    int arr[100];          // local array (fixed size)

    //Initialize MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Take input (only process 0)
    if (rank == 0) {
        printf("Enter number of random values (M):\n");
        scanf("%d", &M);
    }

    //Broadcast M
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Generate random numbers
    srand(time(NULL) + rank); // different seed for each process

    printf("Process %d numbers: ", rank);
    for (int i = 0; i < M; i++) {
        arr[i] = rand() % 100; // random numbers (0–99)
        printf("%d ", arr[i]);

        // find local max
        if (arr[i] > local_max) {
            local_max = arr[i];
        }
    }
    printf("\n");

    //Reduce to find global max
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT,
               MPI_MAX, 0, MPI_COMM_WORLD);

    //Process 0 prints result
    if (rank == 0) {
        printf("Global Maximum = %d\n", global_max);
    }

    //Finalize MPI
    MPI_Finalize();

    return 0;
}

// mpicc 6.c -o 6 && mpirun -np 6 ./6

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 6.c -o 6 && mpirun -np 4 ./6
Enter number of random values:
6
Process 0 numbers: 65 64 7 26 38 37
Process 2 numbers: 57 12 21 94 38 75
Process 3 numbers: 12 71 97 69 17 48
Process 1 numbers: 57 38 96 69 70 65
Global Maximum = 97
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$

sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 6.c -o 6 && mpirun -np 6 ./6
Enter number of random values:
5
Process 0 numbers: 79 75 22 59 43
Process 1 numbers: 21 46 22 60 3
Process 2 numbers: 18 61 45 44 79
Process 3 numbers: 6 47 25 89 71
Process 4 numbers: 95 33 47 2 75
Process 5 numbers: 75 77 81 15 12
Global Maximum = 95

*/