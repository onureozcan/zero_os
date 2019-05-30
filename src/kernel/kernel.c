//
// Created by onureozcan on 28.05.2019.
//
#include <display/console.h>
#include <cpu/gdt.h>

void kmain(void) {
    console_init();
    console_put_string("initializing Zero Os ...\n");
    gdt_init();
}