global gdt_load_kernel_selectors
global gdt_load_user_selectors
global set_gdtr

gdtr: DW 0 ; For limit storage
     DD 0 ; For base storage

set_gdtr:
   ; set global descriptor table pointer
   MOV   EAX, [esp + 4]
   MOV   [gdtr + 2], EAX
   MOV   AX, [ESP + 8]
   MOV   [gdtr], AX
   LGDT  [gdtr]
   RET

gdt_load_kernel_selectors:
   ; Reload CS register containing code selector:
   JMP   0x08:reload_kernel_cs ; 0x08 points at the new code selector
reload_kernel_cs:
   ; Reload data segment registers:
   MOV   AX, 0x10 ; 0x10 points at the new data selector
   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX
   RET

gdt_load_user_selectors:
   ; Reload CS register containing code selector:
   JMP   0x1B:reload_user_cs ; 0x08 points at the new code selector
reload_user_cs:
   ; Reload data segment registers:
   MOV   AX, 0x23 ; 0x10 points at the new data selector
   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX
   RET
