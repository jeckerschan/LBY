#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declare the Assembly function
extern double dot_product_asm(const double *A, const double *B, int n);

// C implementation of the dot product
double dot_product_c(const double *A, const double *B, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}

int main() {
    // Define the size of the arrays
    const int ARRAY_SIZE = 1000000; // 1 million elements

    // Dynamically allocate memory for arrays
    double *A = malloc(ARRAY_SIZE * sizeof(double));
    double *B = malloc(ARRAY_SIZE * sizeof(double));
    if (A == NULL || B == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize arrays with smaller values to prevent overflow
    for (int i = 0; i < ARRAY_SIZE; i++) {
        A[i] = 1.0; // Example: All elements set to 1.0
        B[i] = 1.0;
    }

    // Timing variables
    clock_t start, end;
    double time_c, time_asm;

    // Dot product using C implementation
    start = clock();
    double s_dot_c = dot_product_c(A, B, ARRAY_SIZE);
    end = clock();
    time_c = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Dot product using Assembly implementation
    start = clock();
    double s_dot_asm = dot_product_asm(A, B, ARRAY_SIZE);
    end = clock();
    time_asm = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Display results
    printf("Dot Product (C Kernel): %.6f\n", s_dot_c);
    printf("Execution Time (C Kernel): %.6f seconds\n", time_c);
    printf("Dot Product (Assembly Kernel): %.6f\n", s_dot_asm);
    printf("Execution Time (Assembly Kernel): %.6f seconds\n", time_asm);

    // Free allocated memory
    free(A);
    free(B);

    return 0;
}
