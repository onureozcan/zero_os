//
// Created by onureozcan on 20.07.2019.
//
#include <stdio.h>
#include <stdlib.h>

#include <screen_object.h>
#include <common.h>
#include <canvas.h>

static uint8_t r, g, b;
static canvas_t canvas;

static void repaint(screen_object_t *bkg_object) {

    CLEAR_DIRTY(bkg_object);
    int num_shades = 40;
    int step = bkg_object->height / num_shades;
    int shade = 0;
    for (int i = 0; i < bkg_object->height; i += step, shade++) {
        int h = num_shades > shade ? step : bkg_object->height - i;
        canvas_fill_rect_xy(&canvas, 0, i, r - shade, g - shade, b - shade,
                            h, canvas.width);
    }
}

screen_object_t *background_object_init(int width, int height, int depth) {

    screen_object_t *bkg_object = screen_object_new(NULL, width, height, depth);
    bkg_object->repaint = repaint;
    canvas.height = height;
    canvas.width = width;
    canvas.buffer = bkg_object->buffer;
    canvas.depth = depth;
    r = 96;
    g = 130;
    b = 140;
    return bkg_object;

}