bits 32

extern main
global _start
global make_syscall;

make_syscall:
    mov dword edx,[esp + 4 * 1]
    mov dword ecx,[esp + 4 * 2]
    mov dword ebx,[esp + 4 * 3]
    mov dword eax,[esp + 4 * 4]
    int 80h
    ret

_start:
    call main
    jmp $
