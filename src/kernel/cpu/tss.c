//
// Created by onureozcan on 03.06.2019.
//

#include <cpu/tss.h>
#include <display/console.h>
#include <common.h>
#include <cpu/gdt.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TSS"

void tss_init(uint32_t kernel_stack) {

    console_debug(LOG_TAG, "init called. kernel esp is %p\n", kernel_stack);
    // zero out the tss
    char *tss_as_char = (char *) &tss;
    for (int i = 0; i < sizeof(struct tss_entry); i++) {
        tss_as_char[i] = 0;
    }

    tss.ss0 = 0x10;
    tss.esp0 = kernel_stack;

    tss.cs = 0x0b;
    tss.ss = 0x13;
    tss.es = 0x13;
    tss.ds = 0x13;
    tss.fs = 0x13;
    tss.gs = 0x13;

    tss_flush();

}