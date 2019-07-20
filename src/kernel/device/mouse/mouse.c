//
// Created by onureozcan on 30.06.2019.
//

// https://forum.osdev.org/viewtopic.php?t=10247

#include <device/device.h>
#include <common.h>
#include <memory/memory_manager.h>
#include <display/console.h>
#include <device/mouse/mouse.h>
#include <tasking/task_manager.h>

#define MOUSE_PORT 0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT 0x02
#define MOUSE_BBIT 0x01
#define MOUSE_WRITE 0xD4
#define MOUSE_F_BIT 0x20
#define MOUSE_V_BIT 0x08

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "MOUSE DEVICE"

static uint8_t mouse_click = 0;
static uint8_t mouse_cycle = 0;
static int8_t mouse_byte[3];
static int32_t mouse_pos_x = 0;
static int32_t mouse_pos_y = 0;
static int enabled = FALSE;

static void mouse_wait(uint8_t a_type);

static uint8_t mouse_read() {
    //Get's response from mouse
    mouse_wait(0);
    return read_port(0x60);
}

static void mouse_wait(uint8_t a_type) {
    if (a_type == 0) {
        while (1) //Data
        {
            if ((read_port(0x64) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (1) //Signal
        {
            if ((read_port(0x64) & 2) == 0) {
                return;
            }
        }
        return;
    }
}

static void mouse_write(uint8_t a_write) {
    //Wait to be able to send a command
    mouse_wait(1);
    //Tell the mouse we are sending a command
    write_port(0x64, 0xD4);
    //Wait for the final part
    mouse_wait(1);
    //Finally write
    write_port(0x60, a_write);
}

static int mouse_device_read(struct device *device, char *buffer, int size, int offset) {
    mouse_data_t* data = (mouse_data_t*) buffer;
    data->x = mouse_pos_x;
    data->y = mouse_pos_y;
    data->l_click = mouse_click;
    return 0;
}

static int mouse_device_write(struct device *device, char *buffer, int size, int offset) {
    return 0;
}

static int mouse_device_enable() {
    uint8_t _status; //unsigned char

    //Enable the auxiliary mouse device
    mouse_wait(1);
    write_port(0x64, 0xA8);

    //Enable the interrupts
    mouse_wait(1);
    write_port(0x64, 0x20);
    mouse_wait(0);
    _status = (read_port(0x60) | 2);
    mouse_wait(1);
    write_port(0x64, 0x60);
    mouse_wait(1);
    write_port(0x60, _status);

    //Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read(); //Acknowledge

    //Enable the mouse
    mouse_write(0xF4);
    mouse_read(); //Acknowledge
    enabled = TRUE;
    return 0;
}

static int mouse_device_disable() {
    enabled = FALSE;
    return 0;
}

void mouse_handler() {
    int8_t mouse_x, mouse_y;
    switch(mouse_cycle)
    {
        case 0:
            mouse_byte[0]=read_port(0x60);
            mouse_cycle++;
            break;
        case 1:
            mouse_byte[1]=read_port(0x60);
            mouse_cycle++;
            break;
        case 2:
            mouse_byte[2]=read_port(0x60);
            mouse_x=mouse_byte[1];
            mouse_y=mouse_byte[2];
            if (mouse_byte[0] & 128 || mouse_byte[0] & 64)
                return;

            if (BIT_CHECK(mouse_byte[0],2))
                mouse_y = -mouse_y;
            if (BIT_CHECK(mouse_byte[0],3))
                mouse_x = -mouse_x;
            if (BIT_CHECK(mouse_byte[0],7))
                mouse_click = 1;
            else
                mouse_click = 0;
            mouse_cycle=0;
            mouse_pos_x -= mouse_x;
            mouse_pos_y -= mouse_y;
            break;
    }
    // set next process window manager so that mouse cursor updates will be flawless
    task_manager_set_next_process(window_manager);
}

void mouse_init() {

    device_t *dev = (device_t *) (k_malloc(sizeof(device_t)));
    dev->block_device_props.size_bytes = 3 * sizeof(int);
    dev->type = DEVICE_TYPE_BLOCK;
    dev->device_name = "mouse";
    dev->read = mouse_device_read;
    dev->write = mouse_device_write;
    dev->enable = mouse_device_enable;
    dev->disable = mouse_device_disable;
    device_register(dev);
    console_info(LOG_TAG, "registered mouse device\n");
    mouse_device_enable();
}
