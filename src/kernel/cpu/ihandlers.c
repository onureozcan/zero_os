//
// Created by onureozcan on 03.06.2019.
//

/**
 * This file contains interrupt handlers
 */

#include <stdint-gcc.h>
#include <cpu/idt.h>
#include <display/console.h>
#include <common.h>

/* TIMER */
void irq0_handler(void) {
    write_port(0x20, 0x20); //EOI
}

/*KEYBOARD*/
void irq1_handler(void) {
    console_printf("irq1\n");
    write_port(0x20, 0x20); //EOI
}

void irq2_handler(void) {
    write_port(0x20, 0x20); //EOI
}

void irq3_handler(void) {
    write_port(0x20, 0x20); //EOI
}

void irq4_handler(void) {
    write_port(0x20, 0x20); //EOI
}

void irq5_handler(void) {
    write_port(0x20, 0x20); //EOI
}

void irq6_handler(void) {
    write_port(0x20, 0x20); //EOI
}

void irq7_handler(void) {
    write_port(0x20, 0x20); //EOI
}

void irq8_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI          
}

void irq9_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}

void irq10_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}

void irq11_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}

void irq12_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}

void irq13_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}

void irq14_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}

void irq15_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
}