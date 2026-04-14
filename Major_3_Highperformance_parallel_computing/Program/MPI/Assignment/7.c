
/*Write an MPI program to perform parallel search in an array where process 0 stores an 
integer array of size N and a search key ‘key’. Distribute equal chunks of the array to 
all processes. Each process searches for key in its chunk. If any proce*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int N, key;

    int arr[100];      // full array
    int local_arr[100];

    int found = 0;     // local flag
    int result;        // global result

    //Initialize MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Input (only process 0)
    if (rank == 0) {
        printf("Enter size of array:\n");
        scanf("%d", &N);

        printf("Enter elements:\n");
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }

        printf("Enter key to search:\n");
        scanf("%d", &key);
    }

    //Broadcast N and key
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Calculate chunk size
    int chunk = N / size;

    //Scatter array
    MPI_Scatter(arr, chunk, MPI_INT,
                local_arr, chunk, MPI_INT,
                0, MPI_COMM_WORLD);

    //Each process searches
    for (int i = 0; i < chunk; i++) {
        if (local_arr[i] == key) {
            found = 1;
        }
    }

    //Reduce (logical OR)
    MPI_Reduce(&found, &result, 1, MPI_INT,
               MPI_LOR, 0, MPI_COMM_WORLD);

    //Process 0 prints result
    if (rank == 0) {
        if (result == 1)
            printf("Key found\n");
        else
            printf("Key not found\n");
    }
    //Finalize MPI
    MPI_Finalize();
    return 0;
}



// mpicc 7.c -o 7 && mpirun -np 4 ./7

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 7.c -o 7 && mpirun -np 4 ./7
Enter size of array:
6
Enter elements:
2 3 5 1 6 8
Enter key to search:
5
Key found
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 7.c -o 7 && mpirun -np 4 ./7
Enter size of array:
7
Enter elements:
7 3 5 1 8 4 6
Enter key to search:
9
Key not found
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$
*/