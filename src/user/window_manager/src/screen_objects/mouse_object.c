//
// Created by onureozcan on 20.07.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <screen_object.h>

static char color = 0;
static int memset_size;

static void repaint(screen_object_t *object) {

    CLEAR_DIRTY(object);
    memset(object->buffer, color, memset_size);
}


screen_object_t * mouse_object_init(screen_object_t *parent, int width, int height, int depth) {

    memset_size = width * depth * height;
    screen_object_t *object = screen_object_new(parent, width, height, depth);
    object->repaint = repaint;
    return object;

}