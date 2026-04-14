#include <stdio.h>
#include <mpi.h>

#define N 6

int main(int argc, char * argv[])
{
    
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int A[N][N];
    int x[N];

    int chunk_size = N / size;

    int local_A[chunk_size][N];

    int partial_result[chunk_size];
    int result[N];

    if (rank == 0)
    {
        printf("The Matrix A:\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A[i][j] = i + j;
                x[j] = j+1;
                printf("%d ", A[i][j]);
            }

            printf("\n");
        }
        printf("The Vector X:\n");

        for (int i = 0; i < N; i++)
        {
            printf("%d ", x[i]);
        }
        printf("\n");
        
    }

    MPI_Scatter(A, chunk_size*N, MPI_INT, local_A, chunk_size*N, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received Rows:\n", rank);
    for (int i = 0; i < chunk_size; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", local_A[i][j]);
        }
        printf("\n");
    }
    
    
    MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);


    for (int i = 0; i < chunk_size; i++)
    {
        partial_result[i] = 0;
        for (int j = 0; j < N; j++)
        {
            partial_result[i] = partial_result[i] + local_A[i][j]*x[j];
              
        }
        
    }

    MPI_Gather(partial_result, chunk_size, MPI_INT, result, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    
    if (rank == 0)
    {
        printf("Resultant Vector:\n");
        for (int i = 0; i < N; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
        
    }
    

    MPI_Finalize();
    return 0;
}