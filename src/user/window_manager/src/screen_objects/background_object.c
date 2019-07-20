//
// Created by onureozcan on 20.07.2019.
//
#include <stdio.h>
#include <stdlib.h>

#include <screen_object.h>
#include <common.h>

static char color;
static int memset_size;

static void repaint(screen_object_t *bkg_object) {

    memset(bkg_object->buffer, ++color, memset_size);
}

screen_object_t *background_object_init(int width, int height, int depth) {

    memset_size = width * depth * height;
    screen_object_t *bkg_object = screen_object_new(NULL, width, height, depth);
    bkg_object->repaint = repaint;
    return bkg_object;

}