//
// Created by onureozcan on 04.06.2019.
//

#include <multiboot.h>
#include <display/console.h>
#include <memory/memory_manager.h>
#include <string/k_string.h>
#include <tasking/task_manager.h>
#include <fs/vfs.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define  LOG_TAG "INIT"


void init_load_hello() {
    console_debug(LOG_TAG, "loading hello...\n");
    char *hello_world_bytes;
    int hello_world_size;
    vfs_node_t *hello = vfs_open("/boot/hello", 0);
    if (hello == NULL) {
        console_error(LOG_TAG, "could not find hello app.\n");
        panic(LOG_TAG);
    }
    hello_world_bytes = (char *) (k_malloc(hello->size_bytes));
    hello_world_size = hello->size_bytes;
    vfs_read(hello, hello_world_bytes, hello_world_size, 0);
    task_manager_load_process("hello", hello_world_bytes, NULL, 0);
    k_free(hello_world_bytes);
}