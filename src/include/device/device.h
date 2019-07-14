//
// Created by onureozcan on 29.06.2019.
//

/**
 * Defines an interface for device related things.
 */

#ifndef ZEROOS_DEVICE_H
#define ZEROOS_DEVICE_H

#include <stdint-gcc.h>

#define DEVICE_TYPE_BLOCK 1

typedef struct device {
    struct device *next;
    uint64_t device_id;
    char *device_name;
    uint32_t type;

    /**
     * read from a device.
     * @param buffer buffer to write the data.
     * @param size size of buffer.
     * @param offset offset to start reading from.
     * @return 0 if successful, error code otherwise.
     */
    int (*read)(struct device *device, char *buffer, int size, int offset);

    /**
     * write to a device.
     * @param buffer buffer to read the data.
     * @param size size of buffer.
     * @param offset offset to start writing from.
     * @return 0 if successful, error code otherwise.
     */
    int (*write)(struct device *device, char *buffer, int size, int offset);

    /**
     * enable this device
     * @return 0 if successful, error code otherwise.
     */
    int (*enable)(struct device *device);

    /**
     * disable this device
     * @return 0 if successful, error code otherwise.
     */
    int (*disable)(struct device *device);

    union {
        struct {
            uint64_t size_bytes;
        } block_device_props;
    };
} device_t;

void device_init();

/**
 * register a new device.
 * @return 0 if success, error code otherwise.
 */
int device_register(device_t *);

/**
 * find device by uniq id.
 * @param device_id device id.
 * @return pointer to that device_t.
 */
device_t *device_find(uint64_t device_id);

/**
 * find a device by its name.
 * @param device_name device name.
 * @return pointer to that device_t.
 */
device_t *device_find_by_name(char *device_name);

device_t *devices;

#endif //ZEROOS_DEVICE_H
