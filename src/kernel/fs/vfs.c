//
// Created by onureozcan on 29.06.2019.
//

#include <fs/vfs.h>
#include <display/console.h>
#include <common.h>
#include <memory/memory_manager.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "VFS"

uint64_t volume_id_next;

int vfs_register_volume(vfs_volume_t *vol) {

    vol->next = NULL;
    vol->volume_id = volume_id_next++;
    if (vol->device == NULL) {
        return VFS_ERROR_DEVICE_WAS_NULL;
    }
    if (volumes == NULL) {
        volumes = vol;
    } else {
        vfs_volume_t *current = volumes;
        // insert to the end of list
        while (TRUE) {
            if (current->next == NULL) {
                current->next = vol;
                break;
            }
            current = current->next;
        }
    }
    return 0;
}

int vfs_register_fs(file_system_t *fs) {

    fs->next = NULL;
    if (file_systems == NULL) {
        file_systems = fs;
    } else {
        file_system_t *current = file_systems;
        // insert to the end of list
        while (TRUE) {
            if (current->next == NULL) {
                current->next = fs;
                break;
            }
            current = current->next;
        }
    }
    return 0;
}

vfs_mount_point_t *vfs_get_mount_point_by_path(char *path) {
    vfs_mount_point_t *current = mount_points;
    while (current != NULL) {
        if (strcmp(current->absolute_path, path) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int vfs_register_mount_point(vfs_mount_point_t *mount_point) {
    if (mount_point->volume == NULL) {
        return VFS_ERROR_NO_SUCH_VOLUME;
    }
    if (mount_point->fs == NULL) {
        return VFS_ERROR_NO_SUCH_FS;
    }
    mount_point->next = NULL;
    if (mount_points == NULL) {
        mount_points = mount_point;
    } else {
        vfs_mount_point_t *current = mount_points;
        // insert to the end of list
        while (TRUE) {
            if (current->next == NULL) {
                current->next = mount_point;
                break;
            }
            current = current->next;
        }
    }
    return 0;
}

void vfs_init() {
    console_debug(LOG_TAG, "initializing vfs\n");
}

vfs_volume_t *vfs_find_volume_by_label(char *label) {
    vfs_volume_t *current = volumes;
    while (current != NULL) {
        if (strcmp(current->label, label) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

vfs_node_t *vfs_open(char *full_path, int flags) {
    console_debug(LOG_TAG, "vfs_read %s\n", full_path);
    vfs_mount_point_t *mount_point = vfs_get_mount_point_by_path("/");
    vfs_node_t *ret = (vfs_node_t *) (k_malloc(sizeof(vfs_node_t)));
    vfs_node_t parent = {0};
    vfs_node_t current = {
            .parent = NULL,
            .volume = mount_point->volume
    };
    char file_name_buffer[VFS_MAX_FILE_NAME] = {0};
    int file_name_pos = 1;
    read_path_portion:
    {
        int i = 0;
        while (TRUE) {
            char c = full_path[file_name_pos + i];
            if (c == VFS_FILE_SEPARATOR) {
                file_name_buffer[i] = 0;
                break;
            }
            file_name_buffer[i] = c;
            i++;
            if (full_path[file_name_pos + i] == 0) {
                goto done;
            }
        }
        console_debug(LOG_TAG, "path_portion: %s\n", file_name_buffer);
        current.name = file_name_buffer;
        int try_count = 0;
        int resp;
        try_open:
        {
            if (try_count > 2) {
                return NULL;
            }
            resp = mount_point->fs->open(&current, flags);
            try_count++;
        };
        if (resp == VFS_ERROR_NO_SUCH_FILE) {
            // search for a mount point. if no, then the file is actually absent.
            char *path_to_search_for_a_mount_point = (char *) k_malloc(file_name_pos);
            memcpy(path_to_search_for_a_mount_point, full_path, file_name_pos - 1);
            console_debug(LOG_TAG, "file not found, searching for a mount point at %s ..\n",
                          path_to_search_for_a_mount_point);
            mount_point = vfs_get_mount_point_by_path(path_to_search_for_a_mount_point);
            k_free(path_to_search_for_a_mount_point);
            if (mount_point == NULL) {
                console_debug(LOG_TAG, "no mount points also, file not found\n");
                return NULL;
            } else {
                // open the file with fresh fs and device
                goto try_open;
            }
        } else {
            // parent = current
            memcpy((void *) &parent, &current, sizeof(vfs_node_t));
        }
        file_name_pos += i + 1;
        goto read_path_portion;
    };
    done:
    {
        // ret = current
        memcpy((void *) ret, &current, sizeof(vfs_node_t));
        return ret;
    };

}