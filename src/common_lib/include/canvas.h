//
// Created by onureozcan on 14.06.2019.
//

#ifndef ZEROOS_CANVAS_H
#define ZEROOS_CANVAS_H

#include <stdint-gcc.h>

#define CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS 32

typedef struct canvas {
    char *buffer;
    int width;
    int height;
    int depth;
} canvas_t;

typedef struct point {
    int x;
    int y;
} point_t;


void canvas_fill_rect_xy(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w);

void
canvas_draw_line(canvas_t *canvas, int x, int y, int x2, int y2, uint8_t r, uint8_t g, uint8_t b, uint32_t thickness);

void canvas_put_pixel(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b);

void
canvas_draw_bezier_curve(canvas_t *canvas, int x, int y, point_t points[], int size_of_points, uint8_t r, uint8_t g,
                         uint8_t b, uint32_t thickness);

#endif //ZEROOS_CANVAS_H
