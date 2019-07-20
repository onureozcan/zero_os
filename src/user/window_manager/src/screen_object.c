//
// Created by onureozcan on 15.07.2019.
//
#include <stdio.h>
#include <stdlib.h>

#include <screen_object.h>
#include <common.h>

void screen_object_add_to_parent(screen_object_t *parent, screen_object_t *child);

void screen_object_repaint(screen_object_t *obj) {

    if (IS_DIRTY(obj)) {
        obj->repaint(obj);
        screen_object_t *child = obj->first_child;
        while (child) {
            screen_object_repaint(child);
            child = child->next_sibling;
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
    obj->buffer = malloc(width * height * depth);
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

void screen_object_add_to_parent(screen_object_t *parent, screen_object_t *child) {
    screen_object_t *sibling = parent->first_child;
    while (sibling->next_sibling) {
        sibling = sibling->next_sibling;
    }
    sibling->next_sibling = child;
}