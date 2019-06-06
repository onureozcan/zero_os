//
// Created by onureozcan on 06.06.2019.
//

#include <display/console.h>
#include "tasking/syscall.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "SYSCALL"

void syscall_dispatcher() {
    register int eax asm("eax");
    console_log(LOG_TAG,"called fnc %d\n", eax);
}