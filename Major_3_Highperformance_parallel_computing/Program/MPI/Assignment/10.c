/*
Write an MPI program to approximate the value of π using parallel computation. Use
numerical integration method: 𝜋 ≈ 4x∑(1/(1+xi^2))Δ𝑥(i=0 to N-1), where process 0 decides the
total number of intervals n, divide the computation among all processes. Each process
computes its partial sum. Use MPI_Reduce to add all partial sums. Process 0 prints the
estimated value of π.
*/

#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc,char *argv[]){
    int rank,size;
    double global = 0.0;
    double local = 0.0;
    int n;
    double d_n;
    int base,rem;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0){
        printf("enter intervals: \n");
        scanf("%d",&n);
        d_n = 1.0/n;
    }

    MPI_Bcast(&d_n,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    base = n/size;
    rem = n%size;

    int start = rank * base + (rank < rem ? rank : rem);;
    int end = start + base + (rank < rem ? 1 : 0);

    for(int i = start;i<end;i++){
        double x_i = (i+0)* d_n;
        local += 1.0/(1.0 + x_i * x_i);
    }
    local = local * d_n;
    MPI_Reduce(&local,&global,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank == 0){
        printf("Process 0 prints the estimated value of π : %f\n",4.0*global);
    }

    MPI_Finalize();
    return 0;
}

/*
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 10.c -o 10 && mpirun -np 4 ./10
enter intervals:
5
Process 0 prints the estimated value of π : 3.334926
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$ mpicc 10.c -o 10 && mpirun -np 4 ./10
enter intervals:
7
Process 0 prints the estimated value of π : 3.281048
sukdeb@SUKDEB:~/sukdeb/HPC/MPI/Assignment$
*/

// mpicc 10.c -o 10 && mpirun -np 4 ./10