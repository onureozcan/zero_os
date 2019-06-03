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
#include <keyboard/keyboard.h>

/*GPF*/
void gpf_handler(){
    panic("gpf");
}

/*Double Fault*/
void double_fault_handler(){
    panic("double fault");
}

/* TIMER */
void irq0_handler(void) {
    write_port(0x20, 0x20); //EOI
}

/*KEYBOARD*/
// this function is taken from http://www.osdever.net/bkerndev/Docs/keyboard.htm
void irq1_handler(void) {
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = read_port(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        console_put_char(keyboard_map[scancode]);
    }
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