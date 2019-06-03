//
// Created by onureozcan on 03.06.2019.
//

#include <cpu/idt.h>
#include <cpu/ihandlers.h>

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

void idt_init() {
    idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_ptr.base = (uint32_t) &idt;
    for (int i = 0; i < 256; i++) {
        idt_set_gate(&isr_null, i);
    }
    load_idt(&idt_ptr);
    store_interrupts();
}

