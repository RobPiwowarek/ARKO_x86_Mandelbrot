section .data
four: dq 4.0

section .text
global mandelbrot
    ; registers to preserve (if used) - RBP, RBX, and R12–R15
    ; rdi - pPixelBuffer
    ; rsi - width
    ; rdx - height
    ; xmm0 - x
    ; xmm1 - y
    ; xmm2 - delta
mandelbrot:    
    push rbp
    mov rbp, rsp
    mov rax, rsi
    movsd xmm9, [four]
    movsd xmm8, xmm0    
start:
    ; counter - 0
    ; xmm3 - x0
    ; xmm4 - y0
    mov r9, 0x000000
    movsd xmm3, xmm0
    movsd xmm4, xmm1
calc:
    ; xmm5 - x^2
    ; xmm6 - y^2
    ; xmm7 - x^2 + y^2
    movsd xmm5, xmm3
    mulsd xmm5, xmm5
    
    movsd xmm6, xmm4
    mulsd xmm6, xmm6
 
    movsd xmm7, xmm5
    addsd xmm7, xmm6

    ucomisd xmm7, xmm9
    jnb colour
calcCoords:
    ; xmm7 - x^2 - y^2 + x0
    ; xmm5 - 2xy + y0
    movsd xmm7, xmm5
    subsd xmm7, xmm6
    addsd xmm7, xmm0
    
    movsd xmm5, xmm3
    mulsd xmm5, xmm4
    addsd xmm5, xmm5
    addsd xmm5, xmm1
    movsd xmm4, xmm5

    movsd xmm3, xmm7
cond:
    add r9, 0x010101

    cmp r9, 0xffffff
    jne calc
colour:	
    mov [rdi], r9
    add rdi, 4
next:
    ; xmm0 - xmm0 + delta
    addsd xmm0, xmm2
    dec rax
    jnz start
nextLine:
    ; xmm0 - min x
    ; xmm1 - xmm1 + delta
    movsd xmm0, xmm8
    addsd xmm1, xmm2
    mov rax, rsi
    dec rdx
    jnz start
end:
    mov rsp, rbp
    pop rbp
    ret
