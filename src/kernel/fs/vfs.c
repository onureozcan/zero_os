//
// Created by onureozcan on 29.06.2019.
//

#include <fs/vfs.h>
#include <display/console.h>
#include <common.h>

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

void vfs_init() {

    console_info(LOG_TAG, "initializing vfs\n");

}