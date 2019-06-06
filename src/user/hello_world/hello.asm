bits 32

extern main
global start

start:
    call main
    mov eax,0
    int 0x80 ; syscall test
    jmp $
