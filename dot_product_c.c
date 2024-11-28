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
    const int ARRAY_SIZE = 5; // Example size for this test
    const int NUM_RUNS = 20;  // Number of runs to average execution time

    // Dynamically allocate memory for arrays
    double *A = malloc(ARRAY_SIZE * sizeof(double));
    double *B = malloc(ARRAY_SIZE * sizeof(double));
    if (A == NULL || B == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Sample input values
    double sample_A[] = {1.5, 5.2, 4.5, 2.4, 8.5};
    double sample_B[] = {2.1, 6.5, 8.3, 6.5, 3.5};

    // Initialize arrays
    for (int i = 0; i < ARRAY_SIZE; i++) {
        A[i] = sample_A[i];
        B[i] = sample_B[i];
    }

    // Timing variables
    clock_t start, end;
    double total_time_c = 0.0, total_time_asm = 0.0;
    double s_dot_c, s_dot_asm;

    // Perform NUM_RUNS for C implementation
    for (int i = 0; i < NUM_RUNS; i++) {
        start = clock();
        s_dot_c = dot_product_c(A, B, ARRAY_SIZE);
        end = clock();
        total_time_c += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    // Perform NUM_RUNS for Assembly implementation
    for (int i = 0; i < NUM_RUNS; i++) {
        start = clock();
        s_dot_asm = dot_product_asm(A, B, ARRAY_SIZE);
        end = clock();
        total_time_asm += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    // Calculate average times
    double avg_time_c = total_time_c / NUM_RUNS;
    double avg_time_asm = total_time_asm / NUM_RUNS;

    // Display results
    printf("Dot Product (C Kernel): %.2f\n", s_dot_c);
    printf("Average Execution Time (C Kernel): %.9f seconds\n", avg_time_c);
    printf("Dot Product (Assembly Kernel): %.2f\n", s_dot_asm);
    printf("Average Execution Time (Assembly Kernel): %.9f seconds\n", avg_time_asm);

    // Free allocated memory
    free(A);
    free(B);

    return 0;
}
