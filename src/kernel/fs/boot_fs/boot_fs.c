//
// Created by onureozcan on 29.06.2019.
//

#include <fs/vfs.h>
#include <display/console.h>
#include <common.h>
#include <memory/memory_manager.h>
#include <fs/boot_fs/boot_fs.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "BOOT FS"

static struct multiboot_info *multiboot_struct;

static file_system_t boot_fs;

static void boot_fs_get_boot_module_at(int index, int *size, uint32_t *start) {
    multiboot_module_t *mod = (multiboot_module_t *) multiboot_struct->mods_addr;
    for (int i = 0; i < multiboot_struct->mods_count; i++) {
        if (i == index) {
            *size = mod->mod_end - mod->mod_start;
            *start = mod->mod_start;
            return;
        }
        mod++;
    }
}

int boot_fs_open(vfs_node_t *file, int flags) {
    char *name = file->name;
    console_debug(LOG_TAG, "open:%s\n", name);
    int index = -1;
    if (strcmp(name, "hello") == 0) {
        // load hello world
        index = 0;
    } else if (strcmp(name, "test.txt") == 0) {
        // load test file
        index = 1;
    }
    if (index != -1) {
        int size = 0;
        uint32_t start = 0;
        boot_fs_get_boot_module_at(index, &size, &start);
        file->fs_available = (void *) start; // fs available is start address
        file->size_bytes = size;
        return 0;
    }
    return VFS_ERROR_NO_SUCH_FILE;
}

int boot_fs_read(vfs_node_t *file, char *buffer, int size, int offset) {
    memcpy(buffer, (char *) ((uint32_t) file->fs_available + offset), size);
    return 0;
}

int boot_fs_write(vfs_node_t *file, char *buffer, int size, int offset) {
    return 0;
}

int boot_fs_close(vfs_node_t *file) {
    return 0;
}

void boot_fs_init(struct multiboot_info *mbs) {
    multiboot_struct = mbs;
    boot_fs.name = "boot";
    boot_fs.open = boot_fs_open;
    boot_fs.read = boot_fs_read;
    boot_fs.write = boot_fs_write;
    boot_fs.close = boot_fs_close;
    int ret = vfs_register_fs(&boot_fs);
    if (ret) {
        console_error(LOG_TAG, "could not initialize boot fs. reason: %d\n", ret);
        panic("root fs");
    }
    vfs_mount_point_t *mount_point = (vfs_mount_point_t *) (k_malloc(sizeof(vfs_mount_point_t)));
    mount_point->absolute_path = BOOT_FS_MOUNT_POINT;
    mount_point->volume = vfs_find_volume_by_label("null");
    mount_point->fs = &boot_fs;
    ret = vfs_register_mount_point(mount_point);
    if (ret) {
        console_error(LOG_TAG, "could not initialize a mount point for boot fs. reason: %d\n", ret);
        panic("root fs");
    }
    console_info(LOG_TAG, "registered boot fs\n");

    // mark boot module pages used.
    multiboot_module_t *mod = (multiboot_module_t *) multiboot_struct->mods_addr;
    for (int i = 0; i < multiboot_struct->mods_count; i++) {
        console_debug(LOG_TAG, "module %d start:%p, end: %p\n", i, mod->mod_start, mod->mod_end);
        uint32_t module_page_start = (mod->mod_start / PAGE_SIZE_BYTES);
        uint32_t module_page_end = (mod->mod_end / PAGE_SIZE_BYTES) + 1;
        for (int j = module_page_start; j < module_page_end; j++) {
            memory_manager_mark_page_used(j);
        }
        mod++;
    }
}