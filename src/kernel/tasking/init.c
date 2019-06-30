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
        return;
    }
    hello_world_bytes = (char *) (k_malloc(hello->size_bytes));
    hello_world_size = hello->size_bytes;
    vfs_read(hello, hello_world_bytes, hello_world_size, 0);
    task_manager_load_process("hello", hello_world_bytes, NULL, 0);
    k_free(hello_world_bytes);
}

void init_load_window_manager(int lfb_w, int lfb_h, int lfb_depth) {
    console_debug(LOG_TAG, "loading window manager...\n");
    char *wm_bytes;
    int wm_size;
    vfs_node_t *wm = vfs_open("/boot/window_manager", 0);
    if (wm == NULL) {
        console_error(LOG_TAG, "could not find window manager app.\n");
        panic(LOG_TAG);
        return;
    }
    wm_bytes = (char *) (k_malloc(wm->size_bytes));
    wm_size = wm->size_bytes;
    vfs_read(wm, wm_bytes, wm_size, 0);
    char *c_lfb_w = (char *) lfb_w;
    char *c_lfb_h = (char *) lfb_h;
    char *c_lfb_d = (char *) lfb_depth;
    char *args[] = {c_lfb_w, c_lfb_h, c_lfb_d};
    task_manager_load_process("window manager", wm_bytes, args, 3);
    k_free(wm_bytes);
}