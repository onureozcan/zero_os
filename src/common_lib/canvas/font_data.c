//
// Created by onureozcan on 15.06.2019.
//

#include <canvas.h>

void set_bezier_data_a() {
    simple_bezier_font_table['a'].size = 3;
    simple_bezier_font_table['a'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    30, 50,
                    40, 40,
                    70, 30,
                    90, 50
            }
    };
    simple_bezier_font_table['a'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    90, 50,
                    90, 70,
                    95, 95
            }
    };
    simple_bezier_font_table['a'].layers[2] = (simple_bezier_font_layer_t) {
            .size = 6,
            .data = {
                    90, 90,
                    70, 100,
                    0, 100,
                    0, 80,
                    30, 60,
                    80, 70
            }
    };
}

void set_bezier_data_b() {
    simple_bezier_font_table['b'].size = 2;
    simple_bezier_font_table['b'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    20, 0,
                    20, 0,
                    20, 90
            }
    };
    simple_bezier_font_table['b'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    20, 50,
                    120, 20,
                    120, 120,
                    20, 80
            }
    };
}

void set_bezier_data_c() {
    simple_bezier_font_table['c'].size = 1;
    simple_bezier_font_table['c'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    90, 40,
                    0, 20,
                    0, 100,
                    90, 90
            }
    };
}

void set_bezier_data_d() {
    simple_bezier_font_table['d'].size = 2;
    simple_bezier_font_table['d'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    90, 0,
                    90, 0,
                    90, 90
            }
    };
    simple_bezier_font_table['d'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    90,50,
                    0,10,
                    0,120,
                    90,90
                    }
    };
}

void set_bezier_data_e() {
    simple_bezier_font_table['e'].size = 2;
    simple_bezier_font_table['e'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    20, 60,
                    20, 60,
                    100, 60
            }
    };
    simple_bezier_font_table['e'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 5,
            .data = {
                    100,60,
                    100,30,
                    0,10,
                    -20,100,
                    100,90
            }
    };
}