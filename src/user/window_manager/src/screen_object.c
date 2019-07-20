//
// Created by onureozcan on 15.07.2019.
//
#include <stdio.h>
#include <stdlib.h>

#include <screen_object.h>
#include <common.h>

screen_object_t *screen_object_new(__nullable struct screen_object *parent, int width, int height, int depth) {

    // TODO: add this object to the parent if not null

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
    if (obj->buffer == NULL) {
        printf("could not alloc buffer for object");
        exit(-1);
    }

    return obj;
}