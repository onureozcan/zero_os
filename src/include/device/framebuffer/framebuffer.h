//
// Created by onureozcan on 30.06.2019.
//

/**
 * This file defines an interface to talk with the framebuffer device.
 * It is intended to be used by window manager.
 */
#ifndef ZEROOS_FRAMEBUFFER_H
#define ZEROOS_FRAMEBUFFER_H

void framebuffer_device_register(int size, void *buffer_addr);

#endif //ZEROOS_FRAMEBUFFER_H
