#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes for the C and assembly kernels
float dot_product_c(const float *A, const float *B, int n);
extern float dot_product_asm(const float *A, const float *B, int n);

#define VECTOR_SIZE 1024

int main() {
    float *A = (float *)malloc(VECTOR_SIZE * sizeof(float));
    float *B = (float *)malloc(VECTOR_SIZE * sizeof(float));
    if (!A || !B) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize the vectors with random float values
    srand((unsigned)time(NULL));
    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = (float)(rand() % 100) / 10.0f; // Random float between 0.0 and 9.9
        B[i] = (float)(rand() % 100) / 10.0f; // Random float between 0.0 and 9.9
    }

    // Compute dot product using C kernel
    clock_t start_c = clock();
    float result_c = dot_product_c(A, B, VECTOR_SIZE);
    clock_t end_c = clock();
    double time_c = (double)(end_c - start_c) / CLOCKS_PER_SEC;

    // Compute dot product using assembly kernel
    clock_t start_asm = clock();
    float result_asm = dot_product_asm(A, B, VECTOR_SIZE);
    clock_t end_asm = clock();
    double time_asm = (double)(end_asm - start_asm) / CLOCKS_PER_SEC;

    // Output results
    printf("Dot Product (C Kernel): %.6f\n", result_c);
    printf("Execution Time (C Kernel): %.6f seconds\n", time_c);

    printf("Dot Product (Assembly Kernel): %.6f\n", result_asm);
    printf("Execution Time (Assembly Kernel): %.6f seconds\n", time_asm);

    // Free allocated memory
    free(A);
    free(B);

    return 0;
}

// C Kernel for dot product
float dot_product_c(const float *A, const float *B, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}
