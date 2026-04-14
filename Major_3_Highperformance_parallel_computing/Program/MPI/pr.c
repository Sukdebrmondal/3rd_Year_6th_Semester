#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
    int rank; // ID of the process
    int size;  // no of process 

    // Array defined
    int n=8;  
    int a[8]={3,4,2,7,6,8,6,5};
    int key = 5  // find the key
    int found=0, local_found=0;  // local_found for the each process and found is the global 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int chunk = n / size;
    int start = rank * chunk;
    int end = start + chunk;

    for(int start; start< end; i++){
        if(a[i] == key){
            local_found = 1;
            break;
        }
    }

    MPI_Send(&local_found, 1, MPI_INT, 0, 1,MPI_COMM_WORLD);
        
        if (rank == 0){
            for(int i=0;i<size;i++){
                int temp;
                MPI_Recv(&temp, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_INGORE);
                    if(temp == 1){
                        found =1;
                    }

                if(found){
                    printf("element %d in the arry",key);
                }
                else{
                    printf("element %d in not the arry",key);
                }
            }
        }
        MPI_Finilize();
        return 0;
    
    


}