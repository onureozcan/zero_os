//
// Created by onureozcan on 30.06.2019.
//

#include <fs/vfs.h>
#include <display/console.h>
#include <common.h>
#include <memory/memory_manager.h>
#include <fs/dev_fs/dev_fs.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "DEVICE FS"

static file_system_t dev_fs;

int dev_fs_open(vfs_node_t *file, int flags) {
    char *name = file->name;
    console_debug(LOG_TAG, "open:%s\n", name);
    device_t *device = device_find_by_name(name);
    file->offset_bytes = 0;
    file->size_bytes = 0;
    if (device != NULL && device->type == DEVICE_TYPE_BLOCK) {
        file->fs_available = (void *) device;
        return 0;
    }
    return VFS_ERROR_NO_SUCH_FILE;
}

int dev_fs_read(vfs_node_t *file, char *buffer, int size, int offset) {
    device_t *device = (device_t *) file->fs_available;
    return device->read(buffer, size, offset);
}

int dev_fs_write(vfs_node_t *file, char *buffer, int size, int offset) {
    device_t *device = (device_t *) file->fs_available;
    return device->write(buffer, size, offset);
}

int dev_fs_close(vfs_node_t *file) {
    return 0;
}

void dev_fs_init(struct multiboot_info *mbs) {
    dev_fs.name = "device fs";
    dev_fs.open = dev_fs_open;
    dev_fs.read = dev_fs_read;
    dev_fs.write = dev_fs_write;
    dev_fs.close = dev_fs_close;
    int ret = vfs_register_fs(&dev_fs);
    if (ret) {
        console_error(LOG_TAG, "could not initialize device fs. reason: %d\n", ret);
        panic("root fs");
    }
    vfs_mount_point_t *mount_point = (vfs_mount_point_t *) (k_malloc(sizeof(vfs_mount_point_t)));
    mount_point->absolute_path = DEV_FS_MOUNT_POINT;
    mount_point->volume = vfs_find_volume_by_label("null");
    mount_point->fs = &dev_fs;
    ret = vfs_register_mount_point(mount_point);
    if (ret) {
        console_error(LOG_TAG, "could not initialize a mount point for device fs. reason: %d\n", ret);
        panic("device fs");
    }
    console_info(LOG_TAG, "registered device fs\n");
}