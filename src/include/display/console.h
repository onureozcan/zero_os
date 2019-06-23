/**
 * This file defines an interface for basic logging for 80*25 console.
 */

#ifndef ZEROOS_CONSOLE_H
#define ZEROOS_CONSOLE_H

#include <stdint-gcc.h>

#define CONSOLE_USE_LFB

#ifndef CONSOLE_USE_LFB
#define KERNEL_CONSOLE_WIDTH 80
#define KERNEL_CONSOLE_HEIGHT 25
#else
#define KERNEL_CONSOLE_WIDTH 110
#define KERNEL_CONSOLE_HEIGHT 40
#endif
#define KERNEL_CONSOLE_BUFFER_SIZE (KERNEL_CONSOLE_WIDTH * KERNEL_CONSOLE_HEIGHT)
#define VGA_TEXT_BUFFER_SIZE_CHARS (KERNEL_CONSOLE_WIDTH * KERNEL_CONSOLE_HEIGHT)
#define KERNEL_CONSOLE_BKG_COLOR VGA_COLOR_DARK_GREY
#define KERNEL_CONSOLE_FG_COLOR VGA_COLOR_WHITE
#define VGA_TEXT_MODE_MEMORY_START_ADDRESS 0xB8000

#define KERNEL_CONSOLE_TAB_SPACE_COUNT 4
#define KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE (KERNEL_CONSOLE_WIDTH * 5)

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void console_init();

void console_put_char(char c);

void console_repaint();

void console_put_string(char *str);

void console_printf(const char *fmt, ...);

void console_log(const char *tag, const char *fmt, ...);

void console_clear();

#endif
