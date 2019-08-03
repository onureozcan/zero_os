//
// Created by onureozcan on 20.07.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <screen_object.h>
#include <canvas.h>

#define MOUSE_DRAWING_COORD_WIDTH 150
#define SCALE_MOUSE_DRAWING_COORD_X(x) ((x) * canvas.width / MOUSE_DRAWING_COORD_WIDTH)
#define SCALE_MOUSE_DRAWING_COORD_Y(x) ((x) * canvas.height / MOUSE_DRAWING_COORD_WIDTH)

static uint8_t color = 255;
static canvas_t canvas;
static int line_thickness = 1;

int mouse_shape_coords[][2] = {
        {26,18},
        {26,100},
        {27,19},
        {88,79},
        {88,79},
        {50,79},
        {50,79},
        {26,100}
};

static void repaint(screen_object_t *object) {

    CLEAR_DIRTY(object);
    for(int i = 0; i < 8; i+=2) {
        canvas_draw_line(&canvas, SCALE_MOUSE_DRAWING_COORD_X(mouse_shape_coords[i][0]), SCALE_MOUSE_DRAWING_COORD_Y(mouse_shape_coords[i][1]),
                         SCALE_MOUSE_DRAWING_COORD_X(mouse_shape_coords[i+1][0]), SCALE_MOUSE_DRAWING_COORD_Y(mouse_shape_coords[i+1][1]), color, color, color,
                         line_thickness);
    }
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