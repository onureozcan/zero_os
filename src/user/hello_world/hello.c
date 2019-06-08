//
// Created by onureozcan on 04.06.2019.
//
#include <stdio.h>
#include <stdlib.h>

int test(int i) {
    return i;
}

int main(int argc, char **argv) {
    printf("hello world! This is a user app speaking through write syscall!. %d\n", 4);
    printf("some other thing...\n");
    for (int i = 0; i < 50; i++) {
        printf("test %d\n", test(i));
    }
    printf("apparently printf works just fine\n");
    printf("what about args? argc: %d, argv: %p\n", argc, argv);
}