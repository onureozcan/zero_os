//
// Created by onureozcan on 29.06.2019.
//

#include <fs/vfs.h>
#include <memory/memory_manager.h>
#include <display/console.h>
#include <common.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NULL VOLUME"

void null_volume_register() {

    vfs_volume_t *null_volume = (vfs_volume_t *) (k_malloc(sizeof(vfs_volume_t)));
    null_volume->size = 0;
    null_volume->device = device_find_by_name("null");
    null_volume->label = "null";
    null_volume->offset = 0;
    int ret = vfs_register_volume(null_volume);
    if (ret) {
        console_error(LOG_TAG,"failed to register null volume. reason: %d\n",ret);
        panic("aborted");
    }
    console_info(LOG_TAG, "registered null volume\n");

}