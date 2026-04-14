//Linear Search for any n and any no. of processes (size)
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int n = 8;
    int A[8] = {3, 6, 2, 8, 5, 9, 4, 7};
    int key = 5;

    int local_found = 0, found = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Base chunk size and remainder */
    int base = n / size;
    int rem  = n % size;

    /* Compute start and end indices */
    int start, end;

    if (rank < rem) {
        start = rank * (base + 1);
        end   = start + (base + 1);
    } else {
        start = rank * base + rem;
        end   = start + base;
    }

    /* Local search */
    for (int i = start; i < end; i++) {
        if (A[i] == key) {
            local_found = 1;
            break;
        }
    }
    /* Reduce results using logical OR */
    MPI_Reduce(&local_found, &found, 1, MPI_INT, MPI_LOR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (found)
            printf("Key %d found in array\n", key);
        else
            printf("Key %d not found in array\n", key);
    }

    MPI_Finalize();
    return 0;
}



// MPI_Reduce(
//     void        *sendbuf,
//     void        *recvbuf,
//     int          count,
//     MPI_Datatype datatype,
//     MPI_Op       op,
//     int          root,
//     MPI_Comm     comm
// );
// Parameter	Description
// sendbuf	        Address of the local data sent by each process
// recvbuf	        Address where reduced result is stored  
// count	        Number of elements in sendbuf
// datatype	MPI data type of elements (MPI_INT, MPI_FLOAT, etc.)
// op	                Reduction operation (MPI_SUM, MPI_MAX, MPI_LOR, etc.)
// root	                Rank of process that receives final result
// comm	        Communicator (usually MPI_COMM_WORLD)



// Four Most Important MPI Collectives:
// Function	Purpose
// MPI_Bcast	One → All
// MPI_Scatter	One → Many (divide data)
// MPI_Gather	Many → One (collect data)
// MPI_Reduce	Combine results



// one to all
// MPI_Bcast(
//     void *buffer,
//     int count,
//     MPI_Datatype datatype,
//     int root,
//     MPI_Comm communicator
// );


// one to many
// MPI_Scatter(
//     sendbuf,
//     sendcount,
//     sendtype,
//     recvbuf,
//     recvcount,
//     recvtype,
//     root,
//     communicator
// );


// many to one
// MPI_Gather(
//     sendbuf,
//     sendcount,
//     sendtype,
//     recvbuf,
//     recvcount,
//     recvtype,
//     root,
//     communicator
// );

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