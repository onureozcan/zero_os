; asm part of the simple kernel.
; this file uses tutorial at https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel

;;kernel.asm

;nasm directive - 32 bit
bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x04                  ;flags
        dd - (0x1BADB002 + 0x04) ;checksum. m+f+c should be zero
        resb 20
        dd 0 ; lfb
        dd 1280 ; width pixels
        dd 768 ; height pixels
        dd 32 ; depth

global start
global kernel_esp
extern kmain	        ;kmain is defined in the c file

start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  push eax; GRUB puts multiboot info struct pointer to here
  push ebx;
  call kmain
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space: