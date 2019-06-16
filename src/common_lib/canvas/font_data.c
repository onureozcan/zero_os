//
// Created by onureozcan on 15.06.2019.
//

#include <canvas.h>

#define BEZIER_FONT_HALF_Y 40
#define BEZIER_FONT_FULL_Y 100
#define BEZIER_FONT_FULL_X 90
#define BEZIER_FONT_HALF_X 40

void set_bezier_data_a() {
    simple_bezier_font_table['a'].size = 3;
    simple_bezier_font_table['a'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    30, BEZIER_FONT_HALF_Y + 10,
                    40, BEZIER_FONT_HALF_Y,
                    70, BEZIER_FONT_HALF_Y - 10,
                    90, BEZIER_FONT_HALF_Y + 10
            }
    };
    simple_bezier_font_table['a'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y + 10,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y
            }
    };
    simple_bezier_font_table['a'].layers[2] = (simple_bezier_font_layer_t) {
            .size = 6,
            .data = {
                    90, BEZIER_FONT_FULL_Y - 10,
                    70, BEZIER_FONT_FULL_Y,
                    0, BEZIER_FONT_FULL_Y,
                    0, BEZIER_FONT_FULL_Y - 20,
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
                    20, 100
            }
    };
    simple_bezier_font_table['b'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    20, 50,
                    120, 20,
                    120, 130,
                    20, 90
            }
    };
}

void set_bezier_data_c() {
    simple_bezier_font_table['c'].size = 1;
    simple_bezier_font_table['c'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 6,
            .data = {
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y + 10,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y - 10,
                    0, BEZIER_FONT_HALF_Y,
                    0, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y + 10,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y - 10,
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
                    90, 50,
                    0, 10,
                    0, 120,
                    90, 90
            }
    };
}

void set_bezier_data_e() {
    simple_bezier_font_table['e'].size = 2;
    simple_bezier_font_table['e'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    40, BEZIER_FONT_HALF_Y + 20,
                    40, BEZIER_FONT_HALF_Y + 20,
                    BEZIER_FONT_FULL_X - 20, BEZIER_FONT_HALF_Y + 20
            }
    };
    simple_bezier_font_table['e'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 6,
            .data = {
                    80, BEZIER_FONT_HALF_Y + 20,
                    60, BEZIER_FONT_HALF_Y - 20,
                    0, 30,
                    0, BEZIER_FONT_FULL_Y,
                    30, BEZIER_FONT_FULL_Y,
                    80, BEZIER_FONT_FULL_Y
            }
    };
}

void set_bezier_data_t() {
    simple_bezier_font_table['t'].size = 2;
    simple_bezier_font_table['t'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    BEZIER_FONT_HALF_X, 0,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X + 20, BEZIER_FONT_FULL_Y
            }
    };
    simple_bezier_font_table['t'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, BEZIER_FONT_HALF_Y,
                    10, BEZIER_FONT_HALF_Y,
                    70, BEZIER_FONT_HALF_Y
            }
    };
}

void set_bezier_data_h() {
    simple_bezier_font_table['h'].size = 2;
    simple_bezier_font_table['h'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X - 20, 0,
                    BEZIER_FONT_HALF_X - 20, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X - 20, BEZIER_FONT_FULL_Y
            }
    };
    simple_bezier_font_table['h'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    BEZIER_FONT_HALF_X - 20, BEZIER_FONT_HALF_Y + 20,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y - 10,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y - 10,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y
            }
    };
}

void set_bezier_data_l() {
    simple_bezier_font_table['l'].size = 1;
    simple_bezier_font_table['l'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    BEZIER_FONT_HALF_X, 0,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y - 10,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X + 20, BEZIER_FONT_FULL_Y
            }
    };
}

void set_bezier_data_q() {
    simple_bezier_font_table['q'].size = 2;
    int x_base = (int) (BEZIER_FONT_HALF_X * 1.8f);
    simple_bezier_font_table['q'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    x_base, BEZIER_FONT_HALF_Y,
                    x_base, BEZIER_FONT_FULL_Y,
                    x_base, (int) (BEZIER_FONT_FULL_Y * 1.5f)
            }
    };
    simple_bezier_font_table['q'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    x_base, BEZIER_FONT_HALF_Y,
                    0, BEZIER_FONT_HALF_Y,
                    0, BEZIER_FONT_FULL_Y,
                    x_base, BEZIER_FONT_FULL_Y
            }
    };
}

void set_bezier_data_u() {
    simple_bezier_font_table['u'].size = 1;
    simple_bezier_font_table['u'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 8,
            .data = {
                    20, BEZIER_FONT_HALF_Y,
                    20, BEZIER_FONT_FULL_Y,
                    20, BEZIER_FONT_FULL_Y,
                    20, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X - 20, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X - 20, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X - 20, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X - 20, BEZIER_FONT_HALF_Y,
            }
    };
}

void set_bezier_data_n() {
    simple_bezier_font_table['n'].size = 1;
    simple_bezier_font_table['n'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 8,
            .data = {
                    10, BEZIER_FONT_FULL_Y,
                    10, BEZIER_FONT_HALF_Y,
                    10, BEZIER_FONT_HALF_Y,
                    10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_FULL_Y,
            }
    };
}


void set_bezier_data_j() {
    simple_bezier_font_table['j'].size = 1;
    simple_bezier_font_table['j'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 7,
            .data = {
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_FULL_Y + 40,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_FULL_Y + 40,
                    BEZIER_FONT_HALF_X - 30, BEZIER_FONT_FULL_Y + 40,
            }
    };
}

void set_bezier_data_i() {
    simple_bezier_font_table['i'].size = 2;
    simple_bezier_font_table['i'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 5,
            .data = {
                    BEZIER_FONT_HALF_X - 20, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_FULL_Y,
            }
    };
    simple_bezier_font_table['i'].size = 2;
    simple_bezier_font_table['i'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y - 20,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y - 20,
                    BEZIER_FONT_HALF_X + 10, BEZIER_FONT_HALF_Y - 20,
            }};
}

void set_bezier_data_r() {
    simple_bezier_font_table['r'].size = 2;
    simple_bezier_font_table['r'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_FULL_Y
            }
    };
    simple_bezier_font_table['r'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_HALF_Y + 30,
                    BEZIER_FONT_HALF_X + 20, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y - 10,
                    BEZIER_FONT_HALF_X * 2, BEZIER_FONT_HALF_Y + 10,
            }
    };
}

void set_bezier_data_k() {
    simple_bezier_font_table['k'].size = 3;
    simple_bezier_font_table['k'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X / 2, 0,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_FULL_Y
            }
    };
    simple_bezier_font_table['k'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X * 2, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_HALF_Y + BEZIER_FONT_HALF_Y / 2 + 10,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_HALF_Y + BEZIER_FONT_HALF_Y / 2 + 10,
            }
    };

    simple_bezier_font_table['k'].layers[2] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X * 2, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_HALF_Y + BEZIER_FONT_HALF_Y / 2 + 10,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_HALF_Y + BEZIER_FONT_HALF_Y / 2 + 10,
            }
    };
}

void set_bezier_data_o() {
    simple_bezier_font_table['o'].size = 1;
    simple_bezier_font_table['o'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 7,
            .data = {
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y,
                    -10, BEZIER_FONT_HALF_Y,
                    -10, BEZIER_FONT_FULL_Y + 10,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y + 10,
                    BEZIER_FONT_FULL_X + 10, BEZIER_FONT_FULL_Y + 10,
                    BEZIER_FONT_FULL_X + 10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y
            }
    };
}


void set_bezier_data_m() {
    simple_bezier_font_table['m'].size = 2;
    int top = BEZIER_FONT_HALF_Y - 5;
    simple_bezier_font_table['m'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 6,
            .data = {
                    0, BEZIER_FONT_FULL_Y,
                    0, top,
                    0, top,
                    BEZIER_FONT_HALF_X, top,
                    BEZIER_FONT_HALF_X, top,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y,

            }
    };
    simple_bezier_font_table['m'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 6,
            .data = {
                    BEZIER_FONT_HALF_X + 0, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_HALF_X + 0, top,
                    BEZIER_FONT_HALF_X + 0, top,
                    BEZIER_FONT_HALF_X + BEZIER_FONT_HALF_X, top,
                    BEZIER_FONT_HALF_X + BEZIER_FONT_HALF_X, top,
                    BEZIER_FONT_HALF_X + BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y,

            }
    };

}


void set_bezier_data_w() {
    simple_bezier_font_table['w'].size = 2;
    simple_bezier_font_table['w'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    0, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_FULL_Y + 20,
                    BEZIER_FONT_HALF_X / 2, BEZIER_FONT_FULL_Y + 20,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y,

            }
    };


    simple_bezier_font_table['w'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    BEZIER_FONT_HALF_X, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X / 2 + BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y + 20,
                    BEZIER_FONT_HALF_X / 2 + BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y + 20,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y,
            }
    };

}


void set_bezier_data_f() {
    simple_bezier_font_table['f'].size = 2;
    simple_bezier_font_table['f'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 5,
            .data = {
                    BEZIER_FONT_HALF_X + 20, 0,
                    BEZIER_FONT_HALF_X, 0,
                    BEZIER_FONT_HALF_X, 0,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y + 20,
                    BEZIER_FONT_HALF_X, BEZIER_FONT_FULL_Y + 20,

            }
    };

    simple_bezier_font_table['f'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_HALF_X - 40, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 20, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_HALF_X + 20, BEZIER_FONT_HALF_Y

            }
    };
}


void set_bezier_data_x() {
    simple_bezier_font_table['x'].size = 2;
    simple_bezier_font_table['x'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y

            }
    };

    simple_bezier_font_table['x'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y,
                    10, BEZIER_FONT_FULL_Y,
                    10, BEZIER_FONT_FULL_Y

            }
    };
}

void set_bezier_data_Z() {
    simple_bezier_font_table['Z'].size = 3;
    simple_bezier_font_table['Z'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, 0,
                    BEZIER_FONT_FULL_X, 0,
                    BEZIER_FONT_FULL_X, 0

            }
    };

    simple_bezier_font_table['Z'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_FULL_X - 10, 0,
                    10, BEZIER_FONT_FULL_Y,
                    10, BEZIER_FONT_FULL_Y

            }
    };


    simple_bezier_font_table['Z'].layers[2] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y

            }
    };
}

void set_bezier_data_z() {
    simple_bezier_font_table['z'].size = 3;
    simple_bezier_font_table['z'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y

            }
    };

    simple_bezier_font_table['z'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y,
                    10, BEZIER_FONT_FULL_Y,
                    10, BEZIER_FONT_FULL_Y

            }
    };


    simple_bezier_font_table['z'].layers[2] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y

            }
    };
}