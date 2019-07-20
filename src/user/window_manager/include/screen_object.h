//
// Created by onureozcan on 15.07.2019.
//

#ifndef ZEROOS_SCREEN_OBJECT_H
#define ZEROOS_SCREEN_OBJECT_H

#include <common.h>

typedef struct screen_object {
    int x; // relative to the parent
    int y; // relative to the parent
    int width;
    int height;
    int depth;
    int flags;
    char* buffer;
    struct screen_object *next_sibling;
    struct screen_object *first_child;
    void (*repaint)(struct screen_object*);
} screen_object_t;

screen_object_t* screen_object_new(__nullable struct screen_object* parent, int width, int height, int depth);





#endif //ZEROOS_SCREEN_OBJECT_H
