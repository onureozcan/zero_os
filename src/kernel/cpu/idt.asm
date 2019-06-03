global clear_interrupts
global store_interrupts
global load_idt
global isr_null


clear_interrupts:
    cli
    ret

store_interrupts:
    sti
    ret

load_idt:
    mov dword eax, [esp+4]
    lidt [eax]
    ret

isr_null: NOP
   iret
