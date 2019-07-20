//
// Created by onureozcan on 15.07.2019.
//

#ifndef ZEROOS_SCREEN_OBJECT_H
#define ZEROOS_SCREEN_OBJECT_H

#define SCREEN_OBJ_DIRTY 0

#define IS_DIRTY(obj) BIT_CHECK(obj->flags, SCREEN_OBJ_DIRTY)
#define SET_DIRTY(obj) BIT_SET(obj->flags, SCREEN_OBJ_DIRTY)
#define CLEAR_DIRTY(obj) BIT_CLEAR(obj->flags, SCREEN_OBJ_DIRTY)

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
    struct screen_object *parent; // objects copy their buffer to their parents
    void (*repaint)(struct screen_object*);
} screen_object_t;

screen_object_t* screen_object_new(__nullable screen_object_t* parent, int width, int height, int depth);

void screen_object_repaint(screen_object_t* obj);

void screen_object_relocate(screen_object_t* obj, int x, int y);




#endif //ZEROOS_SCREEN_OBJECT_H
