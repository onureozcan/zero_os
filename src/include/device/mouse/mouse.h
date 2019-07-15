//
// Created by onureozcan on 30.06.2019.
//

#ifndef ZEROOS_MOUSE_H
#define ZEROOS_MOUSE_H

typedef struct mouse_data {
    uint32_t x;
    uint32_t y;
    uint8_t l_click;
    uint8_t r_click;
} mouse_data_t;

void mouse_handler();

void mouse_init();

#endif //ZEROOS_MOUSE_H
