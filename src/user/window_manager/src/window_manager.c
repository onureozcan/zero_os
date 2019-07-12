//
// Created by onureozcan on 30.06.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *lfb;
int depth;
int height;
int width;
char *back_buffer;

int main(int argc, char **argv) {
    printf("argc:%d, argv:%p\n", argc, argv);

    lfb = fopen("/dev/fb0", "wb");
    if (lfb != NULL) {
        printf("opened lfb device at /dev/lfb0\n");
    } else {
        printf("could not open lfb device.\n");
        return -1;
    }
    if (argc < 3) {
        printf("usage: <lfb depth> <lfb width> <lfb height>\n");
        return -1;
    }

    depth = (int) (argv[0]) / 8;
    width = (int) (argv[1]);
    height = (int) (argv[2]);

    printf("width:%d, height:%d, depth:%d\n", width, height, depth);

    back_buffer = (char *) (malloc(width * depth * height));
    if (back_buffer == NULL) {
        printf("could not malloc memory\n");
        return -1;
    }
    int color = 250;
    while(1) {
        memset(back_buffer, color, width * height * depth);
        fwrite(back_buffer, width * height * depth, 1, lfb);
        color++;
    }
}