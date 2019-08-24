//
// Created by onureozcan on 20.07.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <screen_object.h>
#include <canvas/canvas.h>

#define MOUSE_DATA_WIDTH 35
#define MOUSE_DATA_HEIGHT 45

static canvas_t canvas;
static uint8_t *mouse_data;
static FILE *cursor_image_file;
static int mouse_cursor_width;
static int mouse_cursor_height;

static void repaint(screen_object_t *object) {

    CLEAR_DIRTY(object);
    canvas_draw_image(&canvas, mouse_data, 0, 0, MOUSE_DATA_WIDTH, MOUSE_DATA_HEIGHT, mouse_cursor_width,
                      mouse_cursor_height);

}

screen_object_t *mouse_object_init(screen_object_t *parent, int width, int height, int depth) {

    mouse_cursor_width = width;
    mouse_cursor_height = height;
    screen_object_t *object = screen_object_new(parent, width, height, depth);
    object->repaint = repaint;
    canvas.height = height;
    canvas.width = width;
    canvas.buffer = object->buffer;
    canvas.depth = depth;
    // mouse cursor has alpha
    SET_HAS_ALPHA(object);
    cursor_image_file = fopen("/boot/mouse_cursor.data", "rb");
    if (!cursor_image_file) {
        printf("could not open mouse cursor image.\n");
        exit(-1);
    }
    fseek(cursor_image_file, 0, SEEK_END);
    size_t size_of_file = ftell(cursor_image_file);
    fseek(cursor_image_file, 0, SEEK_SET);
    mouse_data = malloc(size_of_file);
    fread(mouse_data, size_of_file, 1, cursor_image_file);

    return object;

}