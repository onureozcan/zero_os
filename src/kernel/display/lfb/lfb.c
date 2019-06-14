//
// Created by onureozcan on 08.06.2019.
//

#include <memory/memory_manager.h>
#include <display/lfb.h>
#include <string/k_string.h>
#include <display/console.h>
#include <canvas.h>

static int lfb_width;
static int lfb_height;
static char *framebuffer;
static char back_buffer[LFB_MAX_SUPPORTED_HEIGHT * LFB_MAX_SUPPORTED_WIDTH * LFB_DEPTH_BYTES];
static int buffer_size;
static int char_width_pixels;
static int char_height_pixels;
static int char_pos;
static int bkg_color = 220;

#define LFB_SCREEN_PADDING_X 100
#define LFB_SCREEN_PADDING_Y 20
#define LFB_LINE_SPACING_X 2
#define LFB_LINE_SPACING_Y 5

canvas_t canvas;

void lfb_init(int height, int width, void *lfb_buffer) {
    lfb_width = width;
    lfb_height = height;
    framebuffer = (char *) lfb_buffer;
    buffer_size = lfb_width * lfb_height * LFB_DEPTH_BYTES;
    lfb_clear();
    char_height_pixels = (height - LFB_SCREEN_PADDING_Y) / KERNEL_CONSOLE_HEIGHT;
    char_width_pixels = (width - LFB_SCREEN_PADDING_X) / KERNEL_CONSOLE_WIDTH;
    canvas_init();
    canvas.depth = LFB_DEPTH_BYTES;
    canvas.buffer = back_buffer;
    canvas.height = height;
    canvas.width = width;
}

void lfb_put_char(char c) {
    char_pos++;
    char_pos %= (KERNEL_CONSOLE_BUFFER_SIZE);

    int col = char_pos / KERNEL_CONSOLE_WIDTH;
    int row = char_pos - col * KERNEL_CONSOLE_WIDTH;

    int x = row * char_width_pixels + (LFB_SCREEN_PADDING_X);
    int y = col * char_height_pixels + (LFB_SCREEN_PADDING_Y);
    int h = char_height_pixels - LFB_LINE_SPACING_Y;
    int w = char_width_pixels - LFB_LINE_SPACING_X;

    canvas_draw_char(&canvas, c, x, y, 0, 0, 0, h, w, 2);
}

void lfb_clear() {
    memset(back_buffer, bkg_color, buffer_size);
}

void lfb_repaint() {
    memcpy(framebuffer, back_buffer, buffer_size);
    lfb_clear();
}

