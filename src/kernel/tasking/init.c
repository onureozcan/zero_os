//
// Created by onureozcan on 04.06.2019.
//

#include <multiboot.h>
#include <display/console.h>
#include <memory/memory_manager.h>
#include <string/k_string.h>
#include <tasking/task_manager.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define  LOG_TAG "INIT"

static char *hello_world_bytes;
static uint32_t hello_world_size;

void init_gather_user_programs_from_boot_modules(struct multiboot_info *multiboot_struct) {
    console_log(LOG_TAG, "getting inital user programs from boot modules\n");
    multiboot_module_t *mod = (multiboot_module_t *) multiboot_struct->mods_addr;
    for (int i = 0; i < multiboot_struct->mods_count; i++) {
        console_log(LOG_TAG, "module %d start:%p, end: %p\n", i, mod->mod_start, mod->mod_end);
        // 0th module hello world
        if (i == 0) {
            hello_world_size = mod->mod_end - mod->mod_start;
            console_log(LOG_TAG, "hello world app has %d bytes, caching in kernel heap\n", hello_world_size);
            hello_world_bytes = k_malloc(hello_world_size);
            memcpy(hello_world_bytes, (const void *) mod->mod_start, hello_world_size);
        }
        mod++;
    }
}

void init_load_hello() {
    console_log(LOG_TAG, "loading hello...\n");
    task_manager_load_process("hello", hello_world_bytes, hello_world_size);
    k_free(hello_world_bytes);
}