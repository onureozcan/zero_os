//
// Created by onureozcan on 03.06.2019.
//

/**
 * This file defines an interface for IDT-related operations
 */

#ifndef ZEROOS_IDT_H
#define ZEROOS_IDT_H

#include <stdint-gcc.h>

struct idt_entry {
    uint16_t offset_lower_bits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higher_bits;
} __attribute__((packed));

struct idt_entry idt[256];

struct idt_ptr {
    unsigned short limit;
    uintptr_t base;
} __attribute__((packed));

/**
 * A noop handler to initially fill the table with
 */
extern void isr_null;

void idt_set_gate(void* isr_address, int index);

struct idt_ptr idt_ptr;

void idt_init();

extern void store_interrupts();

extern void clear_interrupts();

extern void load_idt(void *);

#endif //ZEROOS_IDT_H
