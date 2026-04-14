//Linear search using MPI_scatterv
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int n = 10;
    int A[10] = {3, 6, 2, 8, 5, 9, 4, 7, 1, 10};
    int key = 5;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendcounts[size], displs[size];
    int base = n / size, rem = n % size;

    for (int i = 0; i < size; i++) {
        sendcounts[i] = base + (i < rem ? 1 : 0);
        displs[i] = (i == 0) ? 0 : displs[i-1] + sendcounts[i-1];
    }


    //Creating local array for each process
    int local_n = sendcounts[rank];
    int local_A[local_n];

    MPI_Scatterv(A, sendcounts, displs, MPI_INT,
                 local_A, local_n, MPI_INT,
                 0, MPI_COMM_WORLD);

    int local_found = 0, global_found = 0;

    for (int i = 0; i < local_n; i++) {
        if (local_A[i] == key) {
            local_found = 1;
            break;
        }
    }
    MPI_Reduce(&local_found, &global_found, 1,
               MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (global_found)
            printf("Key %d found\n", key);
        else
            printf("Key %d not found\n", key);
    }

    MPI_Finalize();
    return 0;
}

// many to one with reduction
// MPI_Scatterv(
//     sendbuf,
//     sendcounts,
//     displs,
//     sendtype,
//     recvbuf,
//     recvcount,
//     recvtype,
//     root,
//     communicator
// );
// Array	                Meaning
// sendcounts[i]	How many elements process i gets
// displs[i]	                Starting index for process i