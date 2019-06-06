//
// Created by onureozcan on 03.06.2019.
//

#include <cpu/idt.h>
#include <cpu/ihandlers.h>
#include <common.h>
#include <display/console.h>
#include <tasking/task_manager.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "IDT"

void idt_set_gate(void *isr, int index) {
    uint32_t isr_address = (uint32_t) isr;
    idt[index].offset_lower_bits = isr_address & 0xffff;
    idt[index].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    idt[index].zero = 0;
    idt[index].type_attr = 0x8e; /* INTERRUPT_GATE */
    idt[index].offset_higher_bits = (isr_address & 0xffff0000) >> 16;
}

void idt_set_syscall(void *isr, int index) {
    uint32_t isr_address = (uint32_t) isr;
    idt[index].offset_lower_bits = isr_address & 0xffff;
    idt[index].selector = 0x08; /* USER_CODE_SEGMENT_OFFSET */
    idt[index].zero = 0;
    idt[index].type_attr = 0xEE; /* SYSCALL ATTRS */
    idt[index].offset_higher_bits = (isr_address & 0xffff0000) >> 16;
}

void idt_init() {

    idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_ptr.base = (uint32_t) &idt;

    for (int i = 0; i < 256; i++) {
        idt_set_gate(&isr_null, i);
    }

    idt_set_gate(&double_fault, 8);
    idt_set_gate(&gpf, 13);
    idt_set_gate(&page_fault,14);
    idt_set_syscall(&syscall_fnc, 0x80);

    idt_set_gate(&task_manager_task_switch, 32 + 0);
    idt_set_gate(&irq1, 32 + 1);
    idt_set_gate(&irq2, 32 + 2);
    idt_set_gate(&irq3, 32 + 3);
    idt_set_gate(&irq4, 32 + 4);
    idt_set_gate(&irq5, 32 + 5);
    idt_set_gate(&irq6, 32 + 6);
    idt_set_gate(&irq7, 32 + 7);
    idt_set_gate(&irq8, 32 + 8);
    idt_set_gate(&irq9, 32 + 9);
    idt_set_gate(&irq10, 32 + 10);
    idt_set_gate(&irq11, 32 + 11);
    idt_set_gate(&irq12, 32 + 12);
    idt_set_gate(&irq13, 32 + 13);
    idt_set_gate(&irq14, 32 + 14);
    idt_set_gate(&irq15, 32 + 15);

    console_log(LOG_TAG, "loading idt at %p \n", &idt_ptr);
    load_idt(&idt_ptr);

    console_log(LOG_TAG, "remapping pic\n");
    /* remapping the PIC */
    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);
    write_port(0x21, 0x20);
    write_port(0xA1, 40);
    write_port(0x21, 0x04);
    write_port(0xA1, 0x02);
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    write_port(0x21, 0x0);
    write_port(0xA1, 0x0);

    store_interrupts();
    console_log(LOG_TAG, "restored interrupts\n");

}

