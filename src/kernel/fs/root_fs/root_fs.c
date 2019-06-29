//
// Created by onureozcan on 29.06.2019.
//

#include <fs/vfs.h>
#include <display/console.h>
#include <common.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "ROOT FS"

static file_system_t root_fs;

int root_fs_open(vfs_node_t *file, int flags) {
    return VFS_ERROR_NO_SUCH_FILE;
}

int root_fs_read(vfs_node_t *file, char *buffer, int size, int offset) {
    return 0;
}

int root_fs_write(vfs_node_t *file, char *buffer, int size, int offset) {
    return 0;
}

int root_fs_close(vfs_node_t *file) {
    return 0;
}

void root_fs_init() {
    root_fs.name = "root";
    root_fs.open = root_fs_open;
    root_fs.read = root_fs_read;
    root_fs.write = root_fs_write;
    root_fs.close = root_fs_close;
    int ret = vfs_register_fs(&root_fs);
    if (ret) {
        console_error(LOG_TAG, "could not initialized root fs. reason: %d\n", ret);
        panic("root fs");
    }
    console_debug(LOG_TAG, "registered root fs\n");
}