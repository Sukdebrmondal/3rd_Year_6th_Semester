

// #include<stdio.h>
// #include<omp.h>


// int main(){

//     int n;
//     double product = 0.0;
//     // take user input how many element 
//     printf("Enter the no of threds: ");
//     scanf("%d",&n);

//     // create frist vector
//     double A[n];
//     printf("Enter the elements of first vector:\n");
//     for(int i=0;i<n;i++){
//         scanf("%lf",&A[i]);
//     }
//     // create 2nd vector
//     double B[n];
//     printf("Enter the elements of 2nd vector:\n");
//     for(int i=0;i<n;i++){
//         scanf("%lf",&B[i]);
//     }

//     #pragma omp parallel for reduction(+:product)
//     for(int i=0;i<n;i++){
//         product += A[i] * B[i];
//     }

//     printf("The results of the dot product is %lf: ",product);
//     return 0;
// }



