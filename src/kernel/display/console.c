//
// Created by onureozcan on 29.05.2019.
//

#include <display/console.h>

char kernel_console_buffer[KERNEL_CONSOLE_BUFFER_SIZE] = {0};
int console_buffer_pos = 0;
char *video_memory = (char *) VGA_TEXT_MODE_MEMORY_START_ADDRESS;

void console_put_char_internal(char c);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static void console_repaint() {
    // print the entire buffer
    for (int i = 0; i < VGA_TEXT_BUFFER_SIZE_CHARS; i++) {
        video_memory[i * 2] = kernel_console_buffer[i];
        video_memory[i * 2 + 1] = vga_entry_color(KERNEL_CONSOLE_FG_COLOR, KERNEL_CONSOLE_BKG_COLOR);
    }
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
            break;
        }
        case '\t': {
            for (int i = 0; i < KERNEL_CONSOLE_TAB_SPACE_COUNT; i++) {
                console_put_char(' ');
            }
            break;
        }
        default:
            console_put_char_internal(c);
    }
}

void console_put_char_internal(char c) {
    kernel_console_buffer[console_buffer_pos] = c;
    console_buffer_pos++;
    // scroll if necessary
    if (console_buffer_pos >= KERNEL_CONSOLE_BUFFER_SIZE) {
        int scroll_amount = KERNEL_CONSOLE_WIDTH; // scroll one line
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
    console_repaint();
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