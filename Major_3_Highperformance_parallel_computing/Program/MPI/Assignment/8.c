/*Write an MPI program where all processes form a ring. Each process sends its rank 
value to the next process and receives a value from the previous process and then prints 
the value it received.*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int send_data, recv_data;

    //Initialize MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Determine next and previous process
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    //Data to send
    send_data = rank;

    //Send to next and receive from previous
    MPI_Sendrecv(&send_data, 1, MPI_INT, next, 0,
                 &recv_data, 1, MPI_INT, prev, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //Print received value
    printf("Process %d received %d\n", rank, recv_data);

    //Finalize MPI
    MPI_Finalize();

    return 0;
}

// mpicc 8.c -o 8 && mpirun -np 4 ./8

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 8.c -o 8 && mpirun -np 4 ./8
Process 1 received 0
Process 2 received 1
Process 3 received 2
Process 0 received 3
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 8.c -o 8 && mpirun -np 6 ./8
Process 0 received 5
Process 1 received 0
Process 2 received 1
Process 3 received 2
Process 4 received 3
Process 5 received 4
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$
*/