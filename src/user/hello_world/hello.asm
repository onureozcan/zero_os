bits 32

extern main
global start

start:
    call main
    jmp start
