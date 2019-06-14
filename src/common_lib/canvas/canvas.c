//
// Created by onureozcan on 14.06.2019.
//
#include <canvas.h>

// from osdev
void canvas_fill_rect(canvas_t *canvas, char *where, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w) {
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int t = j * canvas->depth;
            where[t] = r;
            where[t + 1] = g;
            where[t + 2] = b;
        }
        where += canvas->width * canvas->depth;
    }
}

// from osdev
void canvas_fill_rect_xy(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w) {
    uint32_t where = x * canvas->depth + y * canvas->depth * canvas->width;
    canvas_fill_rect(canvas, canvas->buffer + where, r, g, b, h, w);
}

// from osdev
void canvas_put_pixel(canvas_t *canvas, int x, int y, char b, char g, char r) {
    if (x < 0 || x > canvas->width)
        return;
    if (y < 0 || y > canvas->height)
        return;
    // FIXME: what if the depth is of type 32 bits or 16 bits?
    uint32_t where = x * 3 + y * 3 * canvas->width;
    canvas->buffer[where] = b;
    canvas->buffer[where + 1] = g;
    canvas->buffer[where + 2] = r;
}