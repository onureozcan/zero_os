bits 32

extern main
global _start
global make_syscall;

make_syscall:
    mov dword [esp - 4], esp
    mov dword edx,[esp + 4 * 4]
    mov dword ecx,[esp + 4 * 3]
    mov dword ebx,[esp + 4 * 2]
    mov dword eax,[esp + 4 * 1]
    int 80h
    mov esp, [esp - 4]
    ret

_start:
;    push dword 4;
;    push dword 0xFFFFFFFF;
;    push dword 1;
;    push dword 4;
;    call make_syscall
    call main
    jmp _start
