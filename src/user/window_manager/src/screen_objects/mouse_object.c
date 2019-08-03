//
// Created by onureozcan on 20.07.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <screen_object.h>
#include <canvas.h>

static char color = 255;
static canvas_t canvas;

static void repaint(screen_object_t *object) {

    CLEAR_DIRTY(object);
    canvas_fill_rect_xy(&canvas, 0,0, color, color, color, canvas.height, canvas.width);
}


screen_object_t *mouse_object_init(screen_object_t *parent, int width, int height, int depth) {

    screen_object_t *object = screen_object_new(parent, width, height, depth);
    object->repaint = repaint;
    canvas.height = height;
    canvas.width = width;
    canvas.buffer = object->buffer;
    canvas.depth = depth;
    // mouse cursor has alpha
    SET_HAS_ALPHA(object);
    return object;

}