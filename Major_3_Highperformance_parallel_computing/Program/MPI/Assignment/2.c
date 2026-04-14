/*Write an MPI program where process 0 sends a text message to all other processes. 
Every other process receives the message from process 0 and prints: "Process <rank> 
received: <message>". */

// ch

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char message[100];

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Process 0 prepares message
        strcpy(message, "Hello from process 0");

        // Send to all other processes
        for (int i = 1; i < size; i++) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } 
    else {
        // Receive message from process 0
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received: %s\n", rank, message);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

/*

output
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 2.c -o 2
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpirun -np 4 ./2
Process 1 received: Hello from process 0
Process 2 received: Hello from process 0
Process 3 received: Hello from process 0

sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 2.c -o 2
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpirun -np 6 ./2
Process 1 received: Hello from process 0
Process 2 received: Hello from process 0
Process 3 received: Hello from process 0
Process 4 received: Hello from process 0
Process 5 received: Hello from process 0

*/


