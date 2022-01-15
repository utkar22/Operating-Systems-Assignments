section .data
    s1 db "Currently inside function B", 10

section .text
    global B
    extern C

B:
    push rdi
    mov rax, 1
    mov rdi, 1
    mov rsi, s1
    mov rdx, 28
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 8
    syscall
    pop rdi

    lea rax, [C]
    mov [rsp], rax
    ret