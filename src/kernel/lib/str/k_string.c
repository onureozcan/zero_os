//
// Created by onureozcan on 01.06.2019.
//
#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t size) {
    const char *src_as_char = src;
    char *dest_as_char = dest;
    // the most naive implementation.
    // hope compiler optimizes it
    for (size_t i = 0; i < size; i++) {
        dest_as_char[i] = src_as_char[i];
    }
    return dest;
}