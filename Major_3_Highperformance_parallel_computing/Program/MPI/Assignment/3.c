/*Given an integer array of size N stored in process 0, write an MPI program to divide 
the array equally among all processes, each process computes the sum of its part, all 
partial sums are sent back to process 0 and process 0 computes and prints the total sum 
of the array. */


#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    int rank, size; 
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;

    //Input size (only root)
    if (rank == 0) {
        printf("Enter size of array:\n");
        scanf("%d", &n);
    }

    // Broadcast n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int a[n];  // dynamic array

    //Input array (only root)
    if (rank == 0) {
        printf("Enter %d elements:\n", n);
        for (int i = 0; i < n; i++) {
            a[i]=rand() % 20; // random values between 0 and 9
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    // Broadcast full array to all processes
    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);

  
    int chunk = n / size;
    int rem = n % size;

    int start, end;

    if (rank < rem) {
        start = rank * (chunk + 1);
        end = start + (chunk + 1);
    } else {
        start = rank * chunk + rem;
        end = start + chunk;
    }

    //Local computation
    int local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += a[i];
    }

    printf("Process %d → Local sum = %d\n", rank, local_sum);

    //Reduce to get total sum
    int total = 0;

    MPI_Reduce(&local_sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    //Final output
    if (rank == 0) {
        printf("\nTotal sum of array = %d\n", total);
    }

    MPI_Finalize();
    return 0;
}


// output
// sukdeb@SUKDEB:~/sukdeb/HPC/Assignment$ mpicc 3.c -o 3
// sukdeb@SUKDEB:~/sukdeb/HPC/Assignment$ mpirun -np 4 ./3



/*sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 3.c -o 3 && mpirun -np 6 ./3
Enter size of array:
14
Enter 14 elements:
15 17 7 16 11 17 15 9 9 1 1 18 10 18
Process 0 → Local sum = 39
Process 1 → Local sum = 44
Process 3 → Local sum = 10
Process 2 → Local sum = 24
Process 4 → Local sum = 19
Process 5 → Local sum = 28

Total sum of array = 164*/

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 3.c -o 3 && mpirun -np 6 ./3
Enter size of array:
7
Enter 7 elements:
3 9 17 13 12 17 6
Process 0 → Local sum = 12
Process 1 → Local sum = 17
Process 2 → Local sum = 13
Process 4 → Local sum = 17
Process 5 → Local sum = 6
Process 3 → Local sum = 12

Total sum of array = 77
*/