//
// Created by onureozcan on 30.06.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *lfb, *mouse;
int depth;
int height;
int width;
char *back_buffer;

typedef struct mouse_data {
    uint32_t x;
    uint32_t y;
    uint8_t l_click;
    uint8_t r_click;
} mouse_data_t;

mouse_data_t mouse_data_buffer;

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

    lfb = fopen("/dev/fb0", "wb");
    if (lfb != NULL) {
        printf("opened lfb device at /dev/lfb0\n");
    } else {
        printf("could not open lfb device.\n");
        return -1;
    }

    mouse = fopen("/dev/mouse", "r");
    if (mouse != NULL) {
        printf("opened mouse device at /dev/mouse\n");
    } else {
        printf("could not open mouse device.\n");
        return -1;
    }

    back_buffer = (char *) (malloc(width * depth * height));
    if (back_buffer == NULL) {
        printf("could not malloc memory\n");
        return -1;
    } else {
        printf("back buffer at: %p\n", back_buffer);
    }

    int color = 0;
    // dummy loop to make sure that it actually updates the screen
    while (1) {
        fread(&mouse_data_buffer, sizeof(struct mouse_data), 1, mouse);
        fseek(mouse, 0, SEEK_SET);
        memset(back_buffer, color, width * height * depth);
        fwrite(back_buffer, width * height * depth, 1, lfb);
        color++;
    }
}