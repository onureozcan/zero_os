//
// Created by onureozcan on 01.06.2019.
//
#include <stddef.h>
#include <stdint-gcc.h>

void *memcpy(void *dest, void *src, size_t n) {
    uint32_t num_dwords = n / 4;
    uint32_t num_bytes = n % 4;
    uint32_t *dest32 = (uint32_t *) dest;
    uint32_t *src32 = (uint32_t *) src;
    uint8_t *dest8 = ((uint8_t *) dest) + num_dwords * 4;
    uint8_t *src8 = ((uint8_t *) src) + num_dwords * 4;
    uint32_t i;

    for (i = 0; i < num_dwords; i++) {
        dest32[i] = src32[i];
    }
    for (i = 0; i < num_bytes; i++) {
        dest8[i] = src8[i];
    }
    return dest;
}

void *memset(void *b, int c, size_t len) {
    char *s = b;

    while (len--)
        *s++ = c;
    return b;
}