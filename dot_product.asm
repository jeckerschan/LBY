section .text
    global dot_product_asm

dot_product_asm:
    ; Input:
    ;   rcx = pointer to array A
    ;   rdx = pointer to array B
    ;   r8d = number of elements (n)
    ; Output:
    ;   xmm0 = dot product result (double-precision)

    ; Initialize the result accumulator to 0.0
    xorpd xmm0, xmm0        ; xmm0 = 0.0 (initialize accumulator)

    test r8d, r8d           ; Check if n == 0
    jz .done                ; If n == 0, return 0.0

.loop:
    ; Load one element from A and one element from B
    movsd xmm1, [rcx]       ; Load single element from A into xmm1
    movsd xmm2, [rdx]       ; Load single element from B into xmm2
    
    ; Multiply the values in xmm1 and xmm2, store result in xmm1
    mulsd xmm1, xmm2        ; xmm1 = xmm1 * xmm2 (A[i] * B[i])
    
    ; Accumulate the result into xmm0
    addsd xmm0, xmm1        ; xmm0 = xmm0 + xmm1 (accumulate sum)
    
    ; Increment the pointers to the next elements in arrays A and B
    add rcx, 8              ; Increment pointer for A (move by 8 bytes, since double is 8 bytes)
    add rdx, 8              ; Increment pointer for B (move by 8 bytes, since double is 8 bytes)
    
    dec r8d                 ; Decrement the loop counter (n)
    jnz .loop               ; Repeat the loop if n != 0

.done:
    ret                     ; Return the result in xmm0 (dot product)
