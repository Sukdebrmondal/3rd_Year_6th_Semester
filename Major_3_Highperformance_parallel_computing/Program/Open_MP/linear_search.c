#include <stdio.h>
#include <omp.h>

int main() {

    int A[8] = {3, 6, 2, 8, 5, 9, 4, 7};
    int key = 5;
    int found = 0;

    //Race condition as multiple threads update a shared variable
    //Final result depends on execution order

    #pragma omp parallel for
    for (int i = 0; i < 8; i++) {
        if (A[i] == key)
            found = 1;
    }

    /*#pragma omp parallel for
    for (int i = 0; i < 8; i++) {
    if (A[i] == key) {
        #pragma omp critical  //Defines a critical section of code that only one thread can execute at a time
        found = 1;            //Mutual exclusion, so slower                                                                 }                                                                                                                       }*/ 
    /*#pragma omp parallel for reduction(||:found) //Reduction makes it safe by giving each thread its own private copy                                                    //of found. Then combine all thread results using logical OR.
    for (int i = 0; i < 8; i++) {
    if (A[i] == key)
        found = 1;
    }

    if (found)
        printf("Key found\n");
    else
        printf("Key not found\n");

    return 0;*/
}