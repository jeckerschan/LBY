section .data
    ; No static data needed

section .text
    global dot_product_asm

; Function signature: float dot_product_asm(const float *A, const float *B, int n)
dot_product_asm:
    ; Prologue
    push rbp
    mov rbp, rsp
    sub rsp, 16            ; Allocate space for local variables (sum)

    ; Initialize local variable for sum
    xorps xmm0, xmm0       ; xmm0 = 0.0 (accumulator for sum)

    ; Load arguments
    mov rdi, [rbp + 16]    ; A pointer
    mov rsi, [rbp + 24]    ; B pointer
    mov ecx, [rbp + 32]    ; n (vector length)

.loop:
    test ecx, ecx          ; Check if n == 0
    jz .done               ; If n == 0, exit loop

    ; Load A[i] and B[i] into xmm1 and xmm2
    movss xmm1, [rdi]      ; Load A[i]
    movss xmm2, [rsi]      ; Load B[i]

    ; Perform multiplication
    mulss xmm1, xmm2       ; xmm1 = A[i] * B[i]

    ; Add result to accumulator
    addss xmm0, xmm1       ; xmm0 += A[i] * B[i]

    ; Increment pointers
    add rdi, 4             ; Move to next float in A
    add rsi, 4             ; Move to next float in B

    ; Decrement counter
    dec ecx
    jmp .loop

.done:
    ; Store result in memory (sum)
    movss [rsp], xmm0      ; Store sum in local variable

    ; Epilogue
    movss xmm0, [rsp]      ; Return result in xmm0
    add rsp, 16
    pop rbp
    ret
