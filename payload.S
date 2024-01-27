.section .text
.globl _start
_start:
    pushq   %rbp
    movq    %rsp, %rbp
    movabsq $8031924123371070824, %rax
    movq    %rax, -45(%rbp)
    movl    $560229490, -37(%rbp)
    movb    $0, -33(%rbp)
    movl    $1, -4(%rbp)
    leaq    -45(%rbp), %rax
    movq    %rax, -16(%rbp)
    movq    $13, -24(%rbp)
    movl    $1, %eax
    movl    -4(%rbp), %edi
    movq    -16(%rbp), %rsi
    movq    -24(%rbp), %rdx
    syscall
    movq    %rax, -32(%rbp)
    movl    $0, %eax
    popq    %rbp
    ret
