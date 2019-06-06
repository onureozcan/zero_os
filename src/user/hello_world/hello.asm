bits 32

extern main
global _start

global make_syscall:

    int 0x80;

_start:
    call main
    mov eax,0
    int 0x80 ; syscall test
    jmp $
