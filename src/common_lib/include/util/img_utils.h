//
// Created by onureozcan on 24.08.2019.
//

#ifndef ZEROOS_IMG_UTILS_H
#define ZEROOS_IMG_UTILS_H

/**
 * resizes a given raw image data to a desired size.
 * @param src src buffer.
 * @param dest dest buffer.
 * @param src_width width of src image.
 * @param src_height height of src image.
 * @param dest_width width of dest image.
 * @param dest_height height of dest image.
 * @param depth depth of buffers.
 */
void img_util_resize(uint8_t* src, uint8_t* dest, int src_width, int src_height, int dest_width, int dest_height, int depth);

#endif //ZEROOS_IMG_UTILS_H
