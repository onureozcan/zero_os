//
// Created by onureozcan on 04.06.2019.
//

#include <tasking/task_manager.h>
#include <elf/elf.h>
#include <display/console.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TASK_MANAGER"

void task_manager_init() {

}

uint32_t task_manager_load_process(char *name, char *bytes, uint32_t size) {
    Elf32_Ehdr *elf_header = (Elf32_Ehdr*) bytes;
    console_log(LOG_TAG,"load process %s\n", name);

    return 0;
}