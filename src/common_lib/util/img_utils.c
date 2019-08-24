//
// Created by onureozcan on 24.08.2019.
//
#include <stdint-gcc.h>
#include <util/img_utils.h>

static int ceil(float num) {
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}

void img_util_resize(uint8_t *src, uint8_t *dest, int src_width, int src_height, int dest_width, int dest_height,
                     int depth) {

    float x_ratio = ((float) src_width / dest_width);
    float y_ratio = ((float) src_height / dest_height);
    int x_blocks = ceil(x_ratio);
    int y_blocks = ceil(y_ratio);

    float a = x_blocks * y_blocks;

    for (int x = 0; x < dest_width; x++) {
        for (int y = 0; y < dest_height; y++) {
            int src_x = (int) (x_ratio * x);
            int src_y = (int) (y_ratio * y);
            uint32_t sum_r = 0;
            uint32_t sum_g = 0;
            uint32_t sum_b = 0;
            uint32_t sum_a = 0;

            for (int x_block_index = 0; x_block_index < x_blocks; x_block_index++) {
                for (int y_block_index = 0; y_block_index < y_blocks; y_block_index++) {

                    uint8_t *src_ptr = (uint8_t *) &src[depth * src_width * (src_y + y_block_index) + (src_x + x_block_index) * depth];
                    sum_r += *src_ptr++;
                    sum_g += *src_ptr++;
                    sum_b += *src_ptr++;
                    sum_a += *src_ptr;

                }
            }

            uint8_t *dest_ptr = &dest[depth * dest_width * y + x * depth];
            *dest_ptr++ = (uint8_t) (sum_r / a);
            *dest_ptr++ = (uint8_t) (sum_g / a);
            *dest_ptr++ = (uint8_t) (sum_b / a);
            *dest_ptr = (uint8_t) (sum_a / a);
        }
    }
}
