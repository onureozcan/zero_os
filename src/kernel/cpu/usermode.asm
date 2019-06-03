global enter_user_mode
extern inside_user_mode

enter_user_mode:
    cli
    mov ax, 0x23	; user mode data selector is 0x20 (GDT entry 3). Also sets RPL to 3
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push dword 0x23		; SS, notice it uses same selector as above
    push dword esp		; ESP
    pushfd			; EFLAGS
    or    dword [esp], 0x200
    push dword 0x1b		; CS, user mode code selector is 0x18. With RPL 3 this is 0x1b
    mov dword eax, inside_user_mode		; EIP first
    push dword eax
    iretd