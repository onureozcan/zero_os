global task_manager_task_switch

extern irq0_handler
extern current_thread;
extern tasking_enabled;
extern tasking_initial;
extern task_manager_next_task

; this is actually timer handler
task_manager_task_switch:
    pusha

    cmp dword [tasking_initial], 0
    jnz .tasking_initial

    ; call irq handler
    call irq0_handler

    ;test if tasking enabled
    cmp dword [tasking_enabled],0
    jnz .tasking_enabled

    popa
    iret

.tasking_enabled:
    popa
    ;save state of current thread
    mov [esp - 4], eax ; save eax
    mov [esp - 4 -4], ebx ; save ebx

    mov ebx, [current_thread] ; dereference

    mov eax, [esp + 12];
    mov [ebx + 0*4], eax;esp

    mov eax, [esp + 8];
    mov [ebx + 9*4], eax;eflags

    mov eax, [esp + 0];
    mov [ebx + 2*4], eax;eip

    mov [ebx + 1*4], ebp
    mov [ebx + 3*4], edi
    mov [ebx + 4*4], esi
    mov [ebx + 7*4], ecx
    mov [ebx + 8*4], edx

    mov ecx, [esp -4 -4] ; ecx is now ebx
    mov edx, [esp -4] ; edx is now eax

    mov [ebx + 5*4], edx;eax
    mov [ebx + 6*4], ecx;ebx

    jmp .tasking_load_next

.tasking_initial:
    popa
    mov dword [tasking_initial],0

.tasking_load_next:
    ;request next task (will override current_thread)
    call task_manager_next_task

    mov ebx, [current_thread] ; dereference

    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push dword 0x23		;

    mov dword eax, [ebx + 0*4]; esp
    push dword eax		; ESP

    mov eax, [ebx + 9*4] ;eflags
    push dword eax;
    or    dword [esp], 0x200

    push dword 0x1b		; CS

    mov dword eax, [ebx + 2*4]; eip
    push dword eax

    mov ebp, [ebx + 1*4]
    mov edi, [ebx + 3*4]
    mov esi, [ebx + 4*4]
    mov eax, [ebx + 5*4]
    mov ecx, [ebx + 7*4]
    mov edx, [ebx + 8*4]
    mov ebx, [ebx + 6*4]

    iret


