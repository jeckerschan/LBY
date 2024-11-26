section .text
    global dot_product_asm

dot_product_asm:
    ; Function signature: double dot_product_asm(const double *A, const double *B, int n)
    ; Input:
    ;   A - rcx (pointer to array A)
    ;   B - rdx (pointer to array B)
    ;   n - r8d (number of elements)
    ; Output:
    ;   xmm0 - dot product result (double-precision)

    ; Initialize registers
    xorpd xmm0, xmm0        ; xmm0 = 0.0 (accumulator)
    test r8d, r8d           ; Check if n == 0
    jz .done                ; If n == 0, return 0.0

.loop:
    movsd xmm1, [rcx]       ; Load *A into xmm1
    mulsd xmm1, [rdx]       ; xmm1 *= *B
    addsd xmm0, xmm1        ; xmm0 += xmm1
    add rcx, 8              ; Increment A pointer (double size = 8 bytes)
    add rdx, 8              ; Increment B pointer
    dec r8d                 ; Decrement n
    jnz .loop               ; Repeat loop if n != 0

.done:
    ret
