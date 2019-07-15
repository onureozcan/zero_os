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
#include <memory/page_manager.h>
#include <event/event.h>
#include <device/mouse/mouse.h>

/*GPF*/
void gpf_handler(uint32_t error_code) {
    console_printf("!!!gpf: error code %d\n", error_code);
    panic("");
}

/*Double Fault*/
void double_fault_handler() {
    panic("double fault");
}

void page_fault_handler(uint32_t virtual_address) {
    console_printf("page fault %p\n", virtual_address);
    while (1);
}

/* TIMER */
void irq0_handler(void) {
    // publish key event
    event_publish((event_payload_t) {
            .code = EVENT_TIMER_TICK
    });
    write_port(0x20, 0x20); //EOI
}

/*KEYBOARD*/
// this function is taken from http://www.osdever.net/bkerndev/Docs/keyboard.htm
void irq1_handler(void) {
    page_manager_load_kernel_pages();
    uint8_t scancode;

    /* Read from the keyboard's data buffer */
    scancode = read_port(0x60);

    // publish key event
    event_publish((event_payload_t) {
            .code = EVENT_KEYBOARD_EVENT,
            .data.uchar_val = scancode
    });
    write_port(0x20, 0x20); //EOI
    page_manager_restore_pages();
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
    page_manager_load_kernel_pages();
    mouse_handler();
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20); //EOI
    page_manager_restore_pages();
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