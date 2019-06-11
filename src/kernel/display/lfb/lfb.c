//
// Created by onureozcan on 08.06.2019.
//

#include <memory/memory_manager.h>
#include <display/lfb.h>
#include <string/k_string.h>
#include <display/console.h>

static int lfb_width;
static int lfb_height;
static char *framebuffer;
static char back_buffer[LFB_MAX_SUPPORTED_HEIGHT * LFB_MAX_SUPPORTED_WIDTH * LFB_DEPTH_BYTES];
static int buffer_size;
static int char_width_pixels;
static int char_height_pixels;
static int char_pos;
static int bkg_color = 220;

#define LFB_SCREEN_PADDING 20
#define LFB_LINE_SPACING_X 2
#define LFB_LINE_SPACING_Y 5

// TODO: decouple drawing methods and lfb interface

static void fill_rect(char *where, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w) {
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int t = j * LFB_DEPTH_BYTES;
            where[t] = r;
            where[t + 1] = g;
            where[t + 2] = b;
        }
        where += lfb_width * LFB_DEPTH_BYTES;
    }
}

static void fill_rect_xy(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w) {
    uint32_t where = x * LFB_DEPTH_BYTES + y * LFB_DEPTH_BYTES * lfb_width;
    fill_rect(back_buffer + where, r, g, b, h, w);
}

void put_pixel(int x, int y, char b, char g, char r) {
    if (x < 0 || x > lfb_width)
        return;
    if (y < 0 || y > lfb_height)
        return;
    unsigned int where = x * 3 + y * 3 * 1280;
    back_buffer[where] = b;
    back_buffer[where + 1] = g;
    back_buffer[where + 2] = r;
}

//******************

void lfb_init(int height, int width, void *lfb_buffer) {
    lfb_width = width;
    lfb_height = height;
    framebuffer = (char *) lfb_buffer;
    buffer_size = lfb_width * lfb_height * LFB_DEPTH_BYTES;
    lfb_clear();
    char_height_pixels = (height - LFB_SCREEN_PADDING) / KERNEL_CONSOLE_HEIGHT;
    char_width_pixels = (width - LFB_SCREEN_PADDING) / KERNEL_CONSOLE_WIDTH;
}

void lfb_put_char(char c) {
    char_pos++;
    char_pos %= (KERNEL_CONSOLE_BUFFER_SIZE);

    int y = char_pos / KERNEL_CONSOLE_WIDTH;
    int x = char_pos - y * KERNEL_CONSOLE_WIDTH;

    fill_rect_xy(x * char_width_pixels + (LFB_SCREEN_PADDING * 2),
                 y * char_height_pixels + (LFB_SCREEN_PADDING), 0, 0, 0, char_width_pixels - LFB_LINE_SPACING_X,
                 char_height_pixels - LFB_LINE_SPACING_Y);
}

void lfb_clear() {
    memset(back_buffer, bkg_color, buffer_size);
}

void lfb_repaint() {
    memcpy(framebuffer, back_buffer, buffer_size);
    lfb_clear();
}

