
/*Write an MPI program where each process prints its rank and the total number of 
processes in the communicator in the format: "Hello from process <rank> out of <size> 
processes".*/



#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print message
    printf("Hello from process %d out of %d processes\n", rank, size);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}


/*
output
sukdeb@SUKDEB:~/sukdeb/HPC/Assignment$ mpicc 1.c -o 1
sukdeb@SUKDEB:~/sukdeb/HPC/Assignment$ mpirun -np 4 ./1
Hello from process 0 out of 4 processes
Hello from process 1 out of 4 processes
Hello from process 2 out of 4 processes
Hello from process 3 out of 4 processes
sukdeb@SUKDEB:~/sukdeb/HPC/Assignment$
*/


/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 1.c -o 1
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpirun -np 6 ./1
Hello from process 5 out of 6 processes
Hello from process 1 out of 6 processes
Hello from process 3 out of 6 processes
Hello from process 0 out of 6 processes
Hello from process 2 out of 6 processes
Hello from process 4 out of 6 processes
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$
*/