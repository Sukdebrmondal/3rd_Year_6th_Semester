

/*Write an OpenMP program to approximate π using numerical integration. pi = 4 integration(0 to 1)(1/(1+x^2))dx Divide loop iterations among threads. Use reduction to compute the final result.*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main(){

    int interval;
    double d_x,t_sum;
    printf("Enter the number of intervals: \n");
    scanf("%d",&interval);
    d_x = 1.0/interval;
    t_sum = 0;


    #pragma omp parallel for reduction(+:t_sum)
    for(int i = 0;i<interval;i++){
        double x_i = (0.5+i)* d_x;
        t_sum += 1.0/(1.0 + x_i * x_i);
    }

    printf("value of pi is %f \n",4*t_sum*d_x);

}

// To compile: gcc 7.c -fopenmp -o 7
// To run: ./7

/*
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 7.c -fopenmp -o 7
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./7
Enter the number of intervals:
4
value of pi is 3.146801


sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ gcc 7.c -fopenmp -o 7
sukdeb@SUKDEB:~/sukdeb/HPC/Open_MP/Assignment$ ./7
Enter the number of intervals:
7
value of pi is 3.143293


*/