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
    for (int i = 0; i < 5; i++) {
        printf("test %d\n", test(i));
    }
    printf("apparently printf works just fine\n");
    printf("what about args? argc: %d, argv: %p\n", argc, argv);
    printf("1234567890 THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\n");
}