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
#define VFS_ERROR_NO_SUCH_FILE 1
#define VFS_ERROR_NO_SUCH_VOLUME 2
#define VFS_ERROR_NO_SUCH_FS 3

#define VFS_MAX_FILE_NAME 100
#define VFS_FILE_SEPARATOR '/'

typedef struct vfs_volume {
    uint64_t volume_id;
    struct vfs_volume *next;
    char *label;
    device_t *device;
    uint64_t offset;
    uint64_t size;
} vfs_volume_t;

typedef struct vfs_node {
    struct vfs_node *parent;
    char *name;
    char *full_path;
    int flags;
    uint64_t size_bytes;
    vfs_volume_t *volume;
    void* fs;
    void *fs_available;
} vfs_node_t;

typedef struct file_system {
    const char *name;
    struct file_system *next;

    /**
     * opens a file in a given parent.
     * parent can be obtained from {@link vfs_node#parent}
     * name of the file can be obtained from {@link vfs_node#name}
     * @param flags flags.
     * @param file pre-allocated vfs node. fs will fill it in.     *
     * @return 0 if operation is successful, error code if not.
     */
    int (*open)(vfs_node_t *file, int flags);

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


typedef struct vfs_mount_point {
    struct vfs_mount_point* next;
    char *absolute_path;
    vfs_volume_t *volume;
    file_system_t *fs;
} vfs_mount_point_t;

vfs_volume_t *volumes;
file_system_t *file_systems;
vfs_mount_point_t* mount_points;

int vfs_register_mount_point(vfs_mount_point_t* mount_point);

vfs_mount_point_t* vfs_get_mount_point_by_path(char* path);

vfs_volume_t* vfs_find_volume_by_label(char* label);

int vfs_register_volume(vfs_volume_t *vol);

int vfs_register_fs(file_system_t *fs);

void vfs_init();

vfs_node_t *vfs_open(char *full_path, int flags);

int vfs_read(vfs_node_t *file, char *buffer, int size, int offset);

int vfs_write(vfs_node_t *file, char *buffer, int size, int offset);

int vfs_close(vfs_node_t *file);

#endif //ZEROOS_VFS_H
