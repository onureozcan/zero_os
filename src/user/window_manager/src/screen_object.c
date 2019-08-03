//
// Created by onureozcan on 15.07.2019.
//
#include <stdio.h>
#include <stdlib.h>

#include <screen_object.h>
#include <common.h>
#include <assert.h>
#include <unistd.h>

void screen_object_add_to_parent(screen_object_t *parent, screen_object_t *child);

void screen_object_draw_self_on_parent(struct screen_object *parent, screen_object_t *object);

void screen_object_repaint(screen_object_t *obj) {

    if (IS_DIRTY(obj)) {
        obj->repaint(obj);
    }
    screen_object_t *child = obj->first_child;
    while (child) {
        screen_object_repaint(child);
        child = child->next_sibling;
    }
    if (obj->parent) {
        screen_object_draw_self_on_parent(obj->parent, obj);
    }
}

void screen_object_draw_self_on_parent(struct screen_object *parent, screen_object_t *object) {

    int width_parent_bytes = parent->width * parent->depth;
    int width_obj_bytes = object->width * object->depth;

    if (HAS_ALPHA(object)) {
        if (object->depth == DEPTH_32_BITS_ALPHA) {
            for (int i = 0; i < object->width; i++) {
                for (int j = 0; j < object->height; j++) {
                    uint8_t *dest = (uint8_t *)
                                            parent->buffer +
                                    ((object->x + i) * parent->depth + (width_parent_bytes * (j + object->y)));
                    uint8_t *src = (uint8_t *) object->buffer + (i * object->depth + width_obj_bytes * j);
                    uint8_t alpha = src[3]; // 4th byte is alpha.
                    for (int k = 0; k < 3; k++) {
                        // alpha blend
                        *dest = ((*dest * (255 - alpha)) + (*src * alpha)) / 255;
                        dest++;
                        src++;
                    }
                }
            }
        } else {
            printf("object to alpha blend has no alpha channel\n");
            exit(-1);
        }
    } else {
        char *parent_buffer = parent->buffer + width_parent_bytes * object->y + object->x * parent->depth;
        char *object_buffer = object->buffer;
        for (int i = 0; i < object->height; i++) {
            memcpy(parent_buffer, object_buffer, width_obj_bytes);
            parent_buffer += width_parent_bytes;
            object_buffer += width_obj_bytes;
        }
    }
}

screen_object_t *screen_object_new(__nullable screen_object_t *parent, int width, int height, int depth) {

    screen_object_t *obj = malloc(sizeof(screen_object_t));
    if (obj == NULL) {
        printf("could not alloc screen object");
        exit(-1);
    }

    obj->x = 0;
    obj->y = 0;
    obj->height = height;
    obj->width = width;
    obj->depth = depth;
    int size_of_buffer = width * height * depth;
    printf("screen object: size of buffer: %d\n", size_of_buffer);
    obj->buffer = malloc(size_of_buffer);
    obj->next_sibling = NULL;
    obj->first_child = NULL;
    SET_DIRTY(obj);

    if (obj->buffer == NULL) {
        printf("could not alloc buffer for object");
        exit(-1);
    }

    if (parent) {
        screen_object_add_to_parent(parent, obj);
    }

    return obj;
}

void screen_object_relocate(screen_object_t *obj, int x, int y) {

    if (obj->x != x || obj->y != y) {
        screen_object_t *parent = obj->parent;
        SET_DIRTY(parent);
        obj->x = x;
        obj->y = y;
        // bounds_check:
        if (obj->x < 0) {
            obj->x = 0;
        } else if (obj->x + obj->width > parent->width) {
            obj->x = parent->width - obj->width - 1;
        }
        if (obj->y < 0) {
            obj->y = 0;
        } else if (obj->y + obj->height > parent->height) {
            obj->y = parent->height - obj->height - 1;
        }

    }
}

void screen_object_add_to_parent(screen_object_t *parent, screen_object_t *child) {
    screen_object_t *sibling = parent->first_child;
    child->parent = parent;
    if (!sibling) {
        parent->first_child = child;
        return;
    }
    while (sibling->next_sibling) {
        sibling = sibling->next_sibling;
    }
    sibling->next_sibling = child;
}