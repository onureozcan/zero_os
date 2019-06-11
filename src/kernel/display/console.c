//
// Created by onureozcan on 29.05.2019.
//

#include <display/console.h>
#include <stdarg.h>
#include <tinyprintf/tinyprintf.h>
#include <display/lfb.h>

char kernel_console_buffer[KERNEL_CONSOLE_BUFFER_SIZE] = {0};
int console_buffer_pos = 0;
char *video_memory = (char *) VGA_TEXT_MODE_MEMORY_START_ADDRESS;

void console_put_char_internal(char c);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

void console_repaint() {
#ifndef CONSOLE_USE_LFB
    // print the entire buffer
    for (int i = 0; i < VGA_TEXT_BUFFER_SIZE_CHARS; i++) {
        video_memory[i * 2] = kernel_console_buffer[i];
        video_memory[i * 2 + 1] = vga_entry_color(KERNEL_CONSOLE_FG_COLOR, KERNEL_CONSOLE_BKG_COLOR);
    }
#else
    for (int i = 0; i < VGA_TEXT_BUFFER_SIZE_CHARS; i++) {
        lfb_put_char(kernel_console_buffer[i]);
    }
    lfb_repaint();
#endif
}

void console_clear() {
    for (int i = 0; i < KERNEL_CONSOLE_BUFFER_SIZE; i++) {
        kernel_console_buffer[i] = ' ';
    }
    console_buffer_pos = 0;
    console_repaint();
}

void console_put_char(char c) {
    switch (c) {
        case '\n': {
            int line_leftover = KERNEL_CONSOLE_WIDTH - (console_buffer_pos % KERNEL_CONSOLE_WIDTH);
            for (int i = 0; i < line_leftover; i++) {
                console_put_char(' ');
            }
            console_repaint();
            break;
        }
        case '\t': {
            for (int i = 0; i < KERNEL_CONSOLE_TAB_SPACE_COUNT; i++) {
                console_put_char(' ');
            }
            console_repaint();
            break;
        }
        case '\b': {
            if (console_buffer_pos == 0) break;
            console_buffer_pos--;
            console_put_char(' ');
            console_buffer_pos--;
            console_repaint();
            break;
        }
        default:
            console_put_char_internal(c);
    }
}

static void console_buffer_scroll_by_n_chars(int n) {
    int scroll_amount = n;
    for (int i = 0; i < KERNEL_CONSOLE_BUFFER_SIZE - scroll_amount; i++) {
        kernel_console_buffer[i] = kernel_console_buffer[i + scroll_amount];
    }
    // clear scrolled line
    for (int i = 0; i < scroll_amount; i++) {
        kernel_console_buffer[KERNEL_CONSOLE_BUFFER_SIZE - scroll_amount + i] = 0;
    }
    // reposition the cursor
    console_buffer_pos = KERNEL_CONSOLE_BUFFER_SIZE - scroll_amount;
}

void console_put_char_internal(char c) {
    kernel_console_buffer[console_buffer_pos] = c;
    console_buffer_pos++;
    // scroll if necessary
    if (console_buffer_pos >= KERNEL_CONSOLE_BUFFER_SIZE) {
        int scroll_amount = KERNEL_CONSOLE_WIDTH; // scroll one line
        console_buffer_scroll_by_n_chars(scroll_amount);
    }
}

void console_put_string(char *string) {
    int i = 0;
    char c = string[i];
    while (c != 0) {
        console_put_char(c);
        i++;
        c = string[i];
    }
}

void console_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE + 1] = {0};
    tfp_vsnprintf(buffer, KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE, format, args);
    va_end(args);
    console_put_string(buffer);
}

void console_log(const char *tag, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE + 1] = {0};
    tfp_vsnprintf(buffer, KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE, format, args);
    va_end(args);
    console_printf("[%s]:", tag);
    console_put_string(buffer);
}

void console_init() {
    console_clear();
}