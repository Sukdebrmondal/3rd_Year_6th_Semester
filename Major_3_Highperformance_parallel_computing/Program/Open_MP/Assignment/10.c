/*Write  an  OpenMP  program  using #pragma  omp  sectionswhereone  section  computes factorial of a number, 
another section computes Fibonacci seriesand one more section prints prime numbers up to N. Each section runs in parallel.*/

#include<stdio.h>
#include<omp.h>

int fact(int a){
    if(a==0||a == 1){
        return 1;
    }
    else if(a<0){
        return 0;
    }
    else{
        return a*fact(a-1);
    }
}

void fibbo(int n){
    int a = 0,b = 1,c;
    for(int i = 0;i<n;i++){
        printf("%d ",a);
        c = a+b;
        a = b;
        b = c;
    }
    printf("\n");
}

void prime(int n){
    for(int j = 2;j<=n;j++){
        int flag = 1;
        for(int i = 2;i*i<=j;i++){
            if(j%i==0){
                flag = 0;
                break;
            }
        }
        if(flag){
            printf("%d ",j);
        }
    }
    printf("\n");
}


int main(){
    int fac_num = 6;
    int prime_r = 59;
    int fibbo_r = 10;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("The factorial of %d : %d\n",fac_num,fact(fac_num));
        }
        #pragma omp section
        {
            printf("The fibbonaci range upto %d :\n",fibbo_r);
            fibbo(fibbo_r);
            
        }
        #pragma omp section
        {
            printf("The prime range upto %d :\n",prime_r);
            prime(prime_r);
        }
    }
}

// To compile: gcc 10.c -fopenmp -o 10
// To run: ./10

/*
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 10.c -fopenmp -o 10
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./10
The fibbonaci range upto 10 :
0 1 1 2 3 5 8 13 21 34
The factorial of 6 : 720
The prime range upto 59 :
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59

sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 10.c -fopenmp -o 10
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./10
The prime range upto 59 :
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59
The fibbonaci range upto 10 :
0 1 1 2 3 5 8 13 21 34
The factorial of 6 : 720

*/