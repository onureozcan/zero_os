//
// Created by onureozcan on 29.06.2019.
//

#include <device/device.h>
#include <display/console.h>
#include <common.h>
#include <string/k_string.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "DEVICE MANAGER"

static uint64_t device_id_next = 0;

void device_init() {
    console_info(LOG_TAG, "initializing device manager\n");
}

device_t *device_find_by_name(char *name) {
    device_t *current = devices;
    while (current != NULL) {
        if (strcmp(current->device_name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int device_register(device_t *device) {

    device->next = NULL;
    device->device_id = device_id_next++;
    if (devices == NULL) {
        devices = device;
    } else {
        device_t *current = devices;
        // insert to the end of list
        while (TRUE) {
            if (current->next == NULL) {
                current->next = device;
                break;
            }
            current = current->next;
        }
    }

    return 0;
}
