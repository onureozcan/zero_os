//
// Created by onureozcan on 04.06.2019.
//
#include <stdio.h>
#include <stdlib.h>

int test(int i) {
    return i;
}

int main(int argc, char **argv) {
    printf("hello world! This is a user app speaking through write syscall\n");
    printf("some other thing...\n");
    for (int i = 0; i < 5; i++) {
        printf("test %d\n", test(i));
    }
    printf("apparently printf works just fine\n");
    printf("what about args? argc: %d, argv: %p\n", argc, argv);
    printf("trying to open and read a file at /boot/hello.txt\n");
    FILE *file = fopen("/boot/test.txt", "r");
    char buff[200];
    fread(buff, 199, 1, file);
    printf("success. contents:\n\t%s\n", buff);
}