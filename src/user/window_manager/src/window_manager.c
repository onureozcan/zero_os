//
// Created by onureozcan on 30.06.2019.
//

#include <stdio.h>

FILE *lfb;
int depth;
int height;
int width;

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

    depth = (int) (argv[0]);
    width = (int) (argv[1]);
    height = (int) (argv[2]);

    printf("width:%d, height:%d, depth:%d\n", width, height, depth);

}