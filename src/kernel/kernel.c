//
// Created by onureozcan on 28.05.2019.
//
#include <console.h>

void kmain(void) {
    console_clear();
    console_put_string("initializing Zero Os ...");
    for (int i = 0; i < 500; i++) {
        console_put_string("this will trigger scroll");
    }
    return;
}