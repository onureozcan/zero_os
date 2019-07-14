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

static int null_device_read(struct device *device, char *buffer, int size, int offset) {
    memset(buffer, 0, size);
    return 0;
}

static int null_device_write(struct device *device, char *buffer, int size, int offset) {
    return 0;
}

static int null_device_enable(struct device *device) {
    return 0;
}

static int null_device_disable(struct device *device) {
    return 0;
}

void null_device_register() {

    device_t *dev = (device_t *) (k_malloc(sizeof(device_t)));
    dev->type = DEVICE_TYPE_BLOCK;
    dev->block_device_props.size_bytes = 0;
    dev->device_name = "null";
    dev->read = null_device_read;
    dev->enable = null_device_enable;
    dev->disable = null_device_disable;
    dev->write = null_device_write;
    device_register(dev);
    console_info(LOG_TAG, "registered null device\n");

}
