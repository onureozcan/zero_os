//
// Created by onureozcan on 14.06.2019.
//

#ifndef ZEROOS_CANVAS_H
#define ZEROOS_CANVAS_H

#include <stdint-gcc.h>

#define CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS 10
#define CANVAS_SIMPLE_FONT_DEFAULT_SIZE_X 100
#define CANVAS_SIMPLE_FONT_DEFAULT_SIZE_Y 150
#define CANVAS_SIMPLE_FONT_MAX_LAYERS 10

typedef struct canvas {
    char *buffer;
    int width;
    int height;
    int depth;
} canvas_t;

typedef struct point {
    float x;
    float y;
} point_t;

typedef struct simple_bezier_font_layer {
    int size;
    point_t data[CANVAS_SIMPLE_FONT_MAX_LAYERS];
} simple_bezier_font_layer_t;

typedef struct simple_bezier_font {
    int size;
    simple_bezier_font_layer_t layers[CANVAS_SIMPLE_FONT_MAX_LAYERS];
} simple_bezier_font_t;

simple_bezier_font_t simple_bezier_font_table[256];

void canvas_init();

void canvas_blur_xy(canvas_t *canvas, int x, int y, int h, int w , int mult);

void canvas_fill_rect_xy(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w);

void
canvas_draw_line(canvas_t *canvas, int x, int y, int x2, int y2, uint8_t r, uint8_t g, uint8_t b, uint32_t thickness);

void canvas_put_pixel(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b);

void
canvas_draw_bezier_curve(canvas_t *canvas, int x, int y, point_t points[], int size_of_points, uint8_t r, uint8_t g,
                         uint8_t b, uint32_t thickness);

void canvas_draw_char(canvas_t *canvas, int c, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint32_t h, uint32_t w,
                      uint32_t thickness);

#endif //ZEROOS_CANVAS_H
