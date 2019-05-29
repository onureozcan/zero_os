//
// Created by onureozcan on 28.05.2019.
//
#include <display/console.h>
#include <cpu/gdt.h>

void kmain(void) {
    console_clear();
    console_put_string("initializing Zero Os ...");
    console_put_string("gdt_init");
    gdt_init();
    return;
}