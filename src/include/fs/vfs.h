//
// Created by onureozcan on 29.06.2019.
//

/**
 * This file defines a common interface for file system related things.
 */

#include <device/device.h>

#ifndef ZEROOS_VFS_H
#define ZEROOS_VFS_H

#define VFS_ERROR_DEVICE_WAS_NULL 0

typedef struct vfs_volume {
    uint64_t volume_id;
    struct vfs_volume* next;
    char* label;
    device_t* device;
    uint64_t offset;
    uint64_t size;
} vfs_volume_t;

typedef struct vfs_node {
    struct vfs_node *parent;
    char *name;
    int flags;
    void *fs_available;
} vfs_node_t;

typedef struct file_system {
    const char *name;
    struct file_system* next;
    /**
     * opens a file in a given parent.
     * @param parent folder in which the file is located.
     * @param name name of the file.
     * @param flags flags.
     * @param file pre-allocated vfs node. fs will fill it in.     *
     * @return 0 if operation is successful, error code if not.
     */
    int (*open)(vfs_node_t *parent, vfs_node_t *file, char *name, int flags);

    /**
     * reads from a file.
     * @param file file to read.
     * @param buffer buffer to write contents to.
     * @param size size of buffer.
     * @param offset offset from which the read operation will start.
     * @return 0 if operation is successful, error code if not.
     */
    int (*read)(vfs_node_t *file, char *buffer, int size, int offset);

    /**
     * writes to a a file.
     * @param file file to write.
     * @param buffer buffer to write contents from.
     * @param size size of buffer.
     * @param offset offset from which the write operation will start.
     * @return 0 if operation is successful, error code if not.
     */
    int (*write)(vfs_node_t *file, char *buffer, int size, int offset);

    /**
     * closes a file.
     * @param file file to close.
     * @return 0 if operation is successful, error code if not.
     */
    int (*close)(vfs_node_t *file);
} file_system_t;

vfs_volume_t* volumes;
vfs_volume_t* file_systems;

int vfs_register_volume(vfs_volume_t* vol);

void vfs_init();

#endif //ZEROOS_VFS_H
