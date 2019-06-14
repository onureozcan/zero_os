//
// Created by onureozcan on 14.06.2019.
//

#ifndef ZEROOS_CANVAS_H
#define ZEROOS_CANVAS_H

#include <stdint-gcc.h>

typedef struct canvas {
    char *buffer;
    int width;
    int height;
    int depth;
} canvas_t;

void canvas_fill_rect_xy(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w);

void canvas_put_pixel(canvas_t *canvas, int x, int y, char b, char g, char r);

#endif //ZEROOS_CANVAS_H
