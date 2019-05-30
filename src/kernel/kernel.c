//
// Created by onureozcan on 28.05.2019.
//
#include <display/console.h>
#include <cpu/gdt.h>

void kmain(void) {
    console_clear();
    console_put_string("initializing Zero Os ...\n");
    console_put_string("global descriptor table");
    gdt_init();
    console_put_string("...OK");
    return;
}