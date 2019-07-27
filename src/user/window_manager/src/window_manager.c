//
// Created by onureozcan on 30.06.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <screen_object.h>
#include <screen_objects/background_object.h>
#include <screen_objects/mouse_object.h>
#include <canvas.h>

FILE *lfb, *mouse;
int depth;
int height;
int width;

screen_object_t *background_object, *mouse_object;

typedef struct mouse_data {
    uint32_t x;
    uint32_t y;
    uint8_t l_click;
    uint8_t r_click;
} mouse_data_t;

mouse_data_t mouse_data_buffer;

FILE *open_lfb();

FILE *open_mouse();

void update_screen_loop();

void initialize_screen_objects();

void update_mouse_pos();

int main(int argc, char **argv) {

    printf("argc:%d, argv:%p\n", argc, argv);
    if (argc < 3) {
        printf("usage: <lfb depth> <lfb width> <lfb height>\n");
        return -1;
    }
    depth = (int) (argv[0]) / 8;
    width = (int) (argv[1]);
    height = (int) (argv[2]);
    printf("width:%d, height:%d, depth:%d\n", width, height, depth);

    lfb = open_lfb();
    mouse = open_mouse();
    initialize_screen_objects();
    update_screen_loop();
}

void initialize_screen_objects() {
    canvas_init();
    background_object = background_object_init(width, height, depth);
    mouse_object = mouse_object_init(background_object, height / 45, height / 45, depth);
}

void update_screen_loop() {
    int screen_size_bytes = width * height * depth;
    repaint:
    {
        update_mouse_pos();
        screen_object_repaint(background_object);
        fwrite(background_object->buffer, screen_size_bytes, 1, lfb);
        fseek(lfb, 0, SEEK_SET);
        goto repaint;
    }
}

void update_mouse_pos() {
    fread(&mouse_data_buffer, sizeof(struct mouse_data), 1, mouse);
    fseek(mouse, 0, SEEK_SET);
    screen_object_relocate(mouse_object, mouse_data_buffer.x, mouse_data_buffer.y);
}

FILE *open_mouse() {
    FILE *_mouse = fopen("/dev/mouse", "r");
    if (_mouse != NULL) {
        printf("opened mouse device at /dev/mouse\n");
    } else {
        printf("could not open mouse device.\n");
        exit(-1);
    }
    return _mouse;
}

FILE *open_lfb() {
    FILE *_lfb = fopen("/dev/fb0", "wb");
    if (_lfb != NULL) {
        printf("opened lfb device at /dev/lfb0\n");
    } else {
        printf("could not open lfb device.\n");
        exit(-1);
    }
    return _lfb;
}