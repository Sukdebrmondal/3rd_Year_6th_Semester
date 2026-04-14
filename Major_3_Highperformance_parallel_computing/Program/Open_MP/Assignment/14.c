/*Write an OpenMP program to find all prime numbers up to N. Parallelize the checking loop. Use reduction to count total primes.*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int is_prime(int a){
    if(a>0){
        if (a == 1){
            return 0;
        }
        else if(a == 2){
            return 1;
        }
        else{
            for(int i = 2;i*i<=a;i++){
                if(a%i==0){
                    return 0;
                }
            }
            return 1;
        }
    }
}

int main(){
    int n,count = 0;
    printf("Enter the number to check prime upto: \n");
    scanf("%d",&n);

    #pragma omp parallel for reduction(+:count)
    for(int i = 1;i<n;i++){
        if(is_prime(i)){
            count++;
        }
    }
    printf("\nThe Total %d prime numbers upto %d\n",count,n);
    
}

/*


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 14.c -fopenmp -o 14clear
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./14
Enter the number to check prime upto:
11

The Total 4 prime numbers upto 11


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 14.c -fopenmp -o 14clear
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./14
Enter the number to check prime upto:
32

The Total 11 prime numbers upto 32
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$






*/