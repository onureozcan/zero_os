//
// Created by onureozcan on 20.07.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <screen_object.h>
#include <canvas.h>

#define MOUSE_DRAWING_COORD_WIDTH 100
#define MOUSE_DRAWING_COORD_HEIGHT 150
#define MOUSE_SHADOW_RELOCATION 20
#define SCALE_MOUSE_DRAWING_COORD_X(x) ((x) * canvas.width / MOUSE_DRAWING_COORD_WIDTH)
#define SCALE_MOUSE_DRAWING_COORD_Y(x) ((x) * canvas.height / MOUSE_DRAWING_COORD_HEIGHT)

static uint8_t color = 255;
static canvas_t canvas;

static void mouse_object_draw_mouse_cursor(uint8_t _color, uint32_t x_relocate, uint32_t y_relocate, uint8_t alpha);

int mouse_shape_coords[][2] = {
        {0, 0},
        {0, MOUSE_DRAWING_COORD_HEIGHT * 4 / 5},
        {MOUSE_DRAWING_COORD_WIDTH - MOUSE_SHADOW_RELOCATION, MOUSE_DRAWING_COORD_HEIGHT * 3 / 5},
};

static void repaint(screen_object_t *object) {

    CLEAR_DIRTY(object);
    mouse_object_draw_mouse_cursor(50, MOUSE_SHADOW_RELOCATION - 1, MOUSE_SHADOW_RELOCATION / 2, 100);
    // 3x blur for shadow
    for (int i = 0; i < 3; i++)
        canvas_blur_xy(&canvas, 1, 1, canvas.height, canvas.width, 1);
    mouse_object_draw_mouse_cursor(color, 0, 0, 255);
}

static void mouse_object_draw_mouse_cursor(uint8_t _color, uint32_t x_relocate, uint32_t y_relocate, uint8_t alpha) {
    int coords[6];
    // first half
    for (int i = 0; i < 6; i += 2) {
        coords[i] = SCALE_MOUSE_DRAWING_COORD_X(((int *) mouse_shape_coords)[i] + x_relocate);
        coords[i + 1] = SCALE_MOUSE_DRAWING_COORD_Y(((int *) mouse_shape_coords)[i + 1] + y_relocate);
    }
    canvas_fill_triangle(&canvas, coords, _color, _color, _color, alpha);
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