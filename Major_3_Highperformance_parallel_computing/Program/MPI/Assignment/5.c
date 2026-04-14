/*Write an MPI program where process 0 reads an integer value k, broadcast k to all 
processes using MPI_Bcast, each process computes 𝑟𝑒𝑠𝑢𝑙𝑡 = (𝑟𝑎𝑛𝑘 + 1) × 𝑘, process 
0 collects all results and prints them. */



#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int k;                    // input value
    int result;               // local result
    int all_results[100];     // fixed size array (no malloc)

    //Initialize MPI
    MPI_Init(&argc, &argv);

    //Get rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Process 0 takes input
    if (rank == 0) {
        printf("Enter value of k:\n");
        scanf("%d", &k);
    }

    //Broadcast k to all processes
    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Each process computes result
    result = (rank + 1) * k;

    //Gather results in process 0
    MPI_Gather(&result, 1, MPI_INT,
               all_results, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    //Process 0 prints results
    if (rank == 0) {
        printf("Results:\n");
        for (int i = 0; i < size; i++) {
            printf("%d ", all_results[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}


// mpicc 5.c -o 5 && mpirun -np 6 ./5

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 5.c -o 5 && mpirun -np 4 ./5
Enter value of k:
5
Results:
5 10 15 20
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 5.c -o 5 && mpirun -np 6 ./5
Enter value of k:
7
Results:
7 14 21 28 35 42
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$
*/