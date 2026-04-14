// #include <stdio.h>
// #include <mpi.h>

// int main(int argc, char *argv[]) {

//     int rank, size;

//     MPI_Init(&argc, &argv);              // Start MPI environment

//     MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process ID
//     MPI_Comm_size(MPI_COMM_WORLD, &size); // Get number of processes

//     printf("Hello from process %d out of %d processes\n", rank, size);

//     MPI_Finalize();                       // End MPI environment
//     return 0;
// }






#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("hello from %d out of %d process\n", rank, size);

    MPI_Finalize();
    return 0;





}