//
// Created by onureozcan on 08.06.2019.
//
/**
 * This file defines an interface for linear frame buffer drawing
 */

#ifndef ZEROOS_LFB_H
#define ZEROOS_LFB_H

#define LFB_DEPTH_BYTES 4
#define LFB_MAX_SUPPORTED_WIDTH 1280
#define LFB_MAX_SUPPORTED_HEIGHT 768

/**
 * initializes lfb parameters. does not draw anything on screen at this stage since multiboot info is not sanity-checked yet.
 * @param height screen height pixels
 * @param width screen width pixels
 * @param lfb_buffer address of framebuffer
 */
void lfb_init(int height, int width, void *lfb_buffer);

/**
 * clear lfb
 */
void lfb_clear();

/**
 * memcpy back buffer to framebuffer
 */
void lfb_repaint();

/**
 * a handy method resembles console_put_char
 * calculates spaces and character size based on lfb width and height
 * so that 80*25 console and this method behaves the same
 * @param c
 */
void lfb_put_char(char c);

/**
 * kernel does not directly modify lfb.
 */
void lfb_disable();

#endif //ZEROOS_LFB_H
