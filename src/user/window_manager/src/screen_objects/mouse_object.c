//
// Created by onureozcan on 20.07.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <screen_object.h>
#include <canvas.h>

#define MOUSE_DRAWING_COORD_WIDTH 100
#define MOUSE_DRAWING_COORD_HEIGHT 150
#define SCALE_MOUSE_DRAWING_COORD_X(x) ((x) * canvas.width / MOUSE_DRAWING_COORD_WIDTH)
#define SCALE_MOUSE_DRAWING_COORD_Y(x) ((x) * canvas.height / MOUSE_DRAWING_COORD_HEIGHT)

static uint8_t color = 255;
static canvas_t canvas;

static void mouse_object_draw_mouse_cursor(uint8_t color, uint8_t alpha);

int mouse_shape_coords[][2] = {
        {0, 0},
        {0,                         MOUSE_DRAWING_COORD_HEIGHT * 2 / 3 },
        {MOUSE_DRAWING_COORD_WIDTH / 3, MOUSE_DRAWING_COORD_HEIGHT / 2},
        {0, 0},
        {MOUSE_DRAWING_COORD_WIDTH / 3, MOUSE_DRAWING_COORD_HEIGHT / 2},
        {MOUSE_DRAWING_COORD_WIDTH, MOUSE_DRAWING_COORD_HEIGHT / 2}
};

static void repaint(screen_object_t *object) {

    CLEAR_DIRTY(object);
    mouse_object_draw_mouse_cursor(color, 50);
}

static void mouse_object_draw_mouse_cursor(uint8_t color, uint8_t alpha) {
    int coords[6];
    // first half
    for (int i = 0; i < 6; i += 2) {
        coords[i] = SCALE_MOUSE_DRAWING_COORD_X(((int *) mouse_shape_coords)[i]);
        coords[i + 1] = SCALE_MOUSE_DRAWING_COORD_Y(((int *) mouse_shape_coords)[i + 1]);
    }
    canvas_fill_triangle(&canvas, coords, color, color, color, alpha);
    // second half
    for (int i = 0; i < 6; i += 2) {
        coords[i] = SCALE_MOUSE_DRAWING_COORD_X(((int *) mouse_shape_coords)[i + 6]);
        coords[i + 1] = SCALE_MOUSE_DRAWING_COORD_Y(((int *) mouse_shape_coords)[i + 7]);
    }
    canvas_fill_triangle(&canvas, coords, color, color, color, alpha);
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