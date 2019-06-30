//
// Created by onureozcan on 30.06.2019.
//
#include <device/device.h>
#include <memory/memory_manager.h>
#include <display/console.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "FRAMEBUFFER DEVICE"

static char *lfb;
static int fb_size;

static int fb_device_read(char *buffer, int size, int offset) {
    memcpy(buffer, lfb + offset, size);
    return 0;
}

static int fb_device_write(char *buffer, int size, int offset) {
    if (size > fb_size) {
        size = fb_size;
    }
    memcpy(lfb + offset, buffer, size);
    return 0;
}

void framebuffer_device_register(int size, void *buffer_addr) {
    lfb = buffer_addr;
    fb_size = size;
    device_t *dev = (device_t *) (k_malloc(sizeof(device_t)));
    dev->type = DEVICE_TYPE_BLOCK;
    dev->block_device_props.size_bytes = 0;
    dev->device_name = "fb0";
    dev->read = fb_device_read;
    dev->write = fb_device_write;
    device_register(dev);
    console_info(LOG_TAG, "registered framebuffer device. size: %d, lfb address: %p\n", size, buffer_addr);
}