//
// Created by onureozcan on 15.07.2019.
//

#ifndef ZEROOS_SCREEN_OBJECT_H
#define ZEROOS_SCREEN_OBJECT_H

#define DEPTH_32_BITS_ALPHA 4

// needs re-rendering
#define SCREEN_OBJ_DIRTY 0
// needs alpha blend
#define SCREEN_OBJ_HAS_ALPHA 1

#define IS_DIRTY(obj) BIT_CHECK(obj->flags, SCREEN_OBJ_DIRTY)
#define SET_DIRTY(obj) BIT_SET(obj->flags, SCREEN_OBJ_DIRTY)
#define CLEAR_DIRTY(obj) BIT_CLEAR(obj->flags, SCREEN_OBJ_DIRTY)

#define HAS_ALPHA(obj) BIT_CHECK(obj->flags, SCREEN_OBJ_HAS_ALPHA)
#define SET_HAS_ALPHA(obj) BIT_SET(obj->flags, SCREEN_OBJ_HAS_ALPHA)
#define CLEAR_HAS_ALPHA(obj) BIT_CLEAR(obj->flags, SCREEN_OBJ_HAS_ALPHA)

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

void screen_object_init(char* back_buffer, int width, int height, int depth);

screen_object_t* screen_object_new(__nullable screen_object_t* parent, int width, int height, int depth);

void screen_object_repaint(screen_object_t* obj);

void screen_object_relocate(screen_object_t* obj, int x, int y);




#endif //ZEROOS_SCREEN_OBJECT_H
