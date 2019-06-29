//
// Created by onureozcan on 29.06.2019.
//

#include <device/null/null.h>
#include <display/console.h>
#include <device/device.h>
#include <memory/memory_manager.h>
#include <string/k_string.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NULL DEVICE"

static int null_device_read(char *buffer, int size, int offset) {
    memset(buffer, 0, size);
    return 0;
}

static int null_device_write(char *buffer, int size, int offset) {
    return 0;
}

void null_device_register() {

    device_t *dev = (device_t *) (k_malloc(sizeof(device_t)));
    dev->type = DEVICE_TYPE_BLOCK;
    dev->block_device_props.size_bytes = 0;
    dev->device_name = "null";
    dev->read = null_device_read;
    dev->write = null_device_write;
    device_register(dev);
    console_debug(LOG_TAG, "registered null device\n");

}
