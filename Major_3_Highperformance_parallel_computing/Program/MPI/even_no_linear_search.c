#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int n = 8;
    int A[8] = {3, 6, 2, 8, 9, 4, 7, 5};
    int key = 5;
    int found = 0, local_found = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = n / size;
    int start = rank * chunk;
    int end = start + chunk;


    for (int i = start; i < end; i++) {
        if (A[i] == key) {
            local_found = 1;
            break;
        }
    }

    MPI_Send(&local_found, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            int temp;
            MPI_Recv(&temp, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (temp == 1)
                found = 1;
        }

        if (found)
            printf("Key %d found in array\n", key);
        else
            printf("Key %d not found in array\n", key);
    }

    MPI_Finalize();
    return 0;
}


// output
// sukdeb@SUKDEB:~/sukdeb/HPC$ mpicc linear_search.c -o linear_search
// sukdeb@SUKDEB:~/sukdeb/HPC$ mpirun -np 4 ./linear_search
// Key 5 found in array
// sukdeb@SUKDEB:~/sukdeb/HPC$ mpirun -np 4 ./linear_search
// Key 5 found in array
// sukdeb@SUKDEB:~/sukdeb/HPC$ mpicc linear_search.c -o linear_search
// sukdeb@SUKDEB:~/sukdeb/HPC$ mpirun -np 5 ./linear_search
// Key 5 not found in array



// MPI_Send(
//     void *buffer,
//     int count,
//     MPI_Datatype datatype,
//     int destination,
//     int tag,
//     MPI_Comm communicator
// );
// 1.	buffer → data to send
// 2.	count → number of elements
// 3.	datatype → type (MPI_INT, MPI_FLOAT, etc.)
// 4.	destination → rank of receiver
// 5.	tag → message label
// 6.	communicator → usually MPI_COMM_WORLD

// MPI_Recv(
//     void *buffer,
//     int count,
//     MPI_Datatype datatype,
//     int source,
//     int tag,
//     MPI_Comm communicator,
//     MPI_Status *status
// );
// MPI_Status contains info about sender.