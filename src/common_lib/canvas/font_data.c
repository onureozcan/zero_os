//
// Created by onureozcan on 15.06.2019.
//

#include <canvas.h>

#define BEZIER_FONT_HALF_Y 40
#define BEZIER_FONT_FULL_Y 100
#define BEZIER_FONT_FULL_X 90
#define BEZIER_FONT_HALF_X 40

void set_bezier_data_a() {
    simple_bezier_font_table['a'].size = 2;
    simple_bezier_font_table['a'].layers[0] = (simple_bezier_font_layer_t) {.size = 5, .data = {{20,  47},
                                                                                                {38,  34},
                                                                                                {101, 30},
                                                                                                {85,  46},
                                                                                                {85,  100}}};
    simple_bezier_font_table['a'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{85, 86},
                                                                                                {67, 115},
                                                                                                {3,  95},
                                                                                                {2,  98},
                                                                                                {20, 91},
                                                                                                {2,  51},
                                                                                                {54, 64},
                                                                                                {83, 64}}};
}

void set_bezier_data_b() {
    simple_bezier_font_table['b'].size = 2;
    simple_bezier_font_table['b'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{27, 7},
                                                                                                {27, 99}}};
    simple_bezier_font_table['b'].layers[1] = (simple_bezier_font_layer_t) {.size = 9, .data = {{27,  58},
                                                                                                {61,  17},
                                                                                                {127, 44},
                                                                                                {104, 78},
                                                                                                {87,  100},
                                                                                                {71,  100},
                                                                                                {50,  100},
                                                                                                {35,  100},
                                                                                                {27,  92}}};
}

void set_bezier_data_c() {
    simple_bezier_font_table['c'].size = 1;
    simple_bezier_font_table['c'].layers[0] = (simple_bezier_font_layer_t) {.size = 6, .data = {{85,  50},
                                                                                                {65,  35},
                                                                                                {-10, 30},
                                                                                                {-10, 82},
                                                                                                {25,  119},
                                                                                                {85,  89}}};
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
    simple_bezier_font_table['e'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{36, 71},
                                                                                                {99, 71}}};
    simple_bezier_font_table['e'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{98,  71},
                                                                                                {93,  37},
                                                                                                {80,  27},
                                                                                                {12,  27},
                                                                                                {-1,  72},
                                                                                                {31,  109},
                                                                                                {61,  115},
                                                                                                {103, 90}}};
}

void set_bezier_data_t() {
    simple_bezier_font_table['t'].size = 3;
    simple_bezier_font_table['t'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{49, 5},
                                                                                                {49, 99}}};
    simple_bezier_font_table['t'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{50, 99},
                                                                                                {75, 99}}};
    simple_bezier_font_table['t'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 40},
                                                                                                {75, 40}}};
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
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y - 15,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_HALF_Y - 15,
                    BEZIER_FONT_FULL_X, BEZIER_FONT_FULL_Y
            }
    };
}

void set_bezier_data_l() {
    simple_bezier_font_table['l'].size = 2;
    simple_bezier_font_table['l'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{49, 5},
                                                                                                {49, 99}}};
    simple_bezier_font_table['l'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{28, 99},
                                                                                                {85, 99}}};
}

void set_bezier_data_q() {
    simple_bezier_font_table['q'].size = 2;
    simple_bezier_font_table['q'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{87, 45},
                                                                                                {87, 135}}};
    simple_bezier_font_table['q'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{87, 50},
                                                                                                {65, 40},
                                                                                                {27, 30},
                                                                                                {13, 60},
                                                                                                {5,  100},
                                                                                                {55, 110},
                                                                                                {75, 100},
                                                                                                {87, 88}}};
}

void set_bezier_data_u() {
    simple_bezier_font_table['u'].size = 2;
    simple_bezier_font_table['u'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{85, 41},
                                                                                                {85, 95}}};
    simple_bezier_font_table['u'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{85, 83},
                                                                                                {54, 99},
                                                                                                {10, 123},
                                                                                                {20, 40}}};
}

void set_bezier_data_n() {
    simple_bezier_font_table['n'].size = 2;
    simple_bezier_font_table['n'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{23, 100},
                                                                                                {23, 40}}};
    simple_bezier_font_table['n'].layers[1] = (simple_bezier_font_layer_t) {.size = 6, .data = {{25,  57},
                                                                                                {69,  23},
                                                                                                {100, 44},
                                                                                                {89,  81},
                                                                                                {90,  65},
                                                                                                {90,  99}}};
}

void set_bezier_data_j() {

    simple_bezier_font_table['j'].size = 3;
    simple_bezier_font_table['j'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 2,
            .data = {{36, 40},
                     {75, 40}

            }
    };
    simple_bezier_font_table['j'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {{50, 104},
                     {40, 110},
                     {21, 109}

            }
    };
    simple_bezier_font_table['j'].layers[2] = (simple_bezier_font_layer_t) {
            .size = 2,
            .data = {{53, 41},
                     {53, 104}

            }
    };

}

void set_bezier_data_i() {
    simple_bezier_font_table['i'].size = 3;
    simple_bezier_font_table['i'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{40, 45},
                                                                                                {70, 45}}};
    simple_bezier_font_table['i'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{60, 45},
                                                                                                {60, 95}}};
    simple_bezier_font_table['i'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{55, 20},
                                                                                                {65, 20}}};
}

void set_bezier_data_r() {
    simple_bezier_font_table['r'].size = 2;
    simple_bezier_font_table['r'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{30, 40},
                                                                                                {30, 99}}};
    simple_bezier_font_table['r'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{30, 62},
                                                                                                {55, 35},
                                                                                                {85, 32},
                                                                                                {90, 45}}};
}

void set_bezier_data_k() {
    simple_bezier_font_table['k'].size = 3;
    simple_bezier_font_table['k'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{25, 4},
                                                                                                {25, 100}}};
    simple_bezier_font_table['k'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{84, 42},
                                                                                                {26, 75}}};
    simple_bezier_font_table['k'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{45, 67},
                                                                                                {84, 100}}};
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
    simple_bezier_font_table['m'].size = 3;
    simple_bezier_font_table['m'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{18, 99},
                                                                                                {18, 39}}};
    simple_bezier_font_table['m'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{20, 66},
                                                                                                {44, 24},
                                                                                                {58, 30},
                                                                                                {55, 100}}};
    simple_bezier_font_table['m'].layers[2] = (simple_bezier_font_layer_t) {.size = 4, .data = {{55, 65},
                                                                                                {80, 18},
                                                                                                {91, 45},
                                                                                                {90, 100}}};
}


void set_bezier_data_w() {
    simple_bezier_font_table['w'].size = 4;
    simple_bezier_font_table['w'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{5,  40},
                                                                                                {31, 97}}};
    simple_bezier_font_table['w'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{32, 95},
                                                                                                {51, 59}}};
    simple_bezier_font_table['w'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{52, 60},
                                                                                                {71, 97}}};
    simple_bezier_font_table['w'].layers[3] = (simple_bezier_font_layer_t) {.size = 2, .data = {{70, 97},
                                                                                                {95, 40}}};
}


void set_bezier_data_f() {
    simple_bezier_font_table['f'].size = 3;
    simple_bezier_font_table['f'].layers[0] = (simple_bezier_font_layer_t) {.size = 4, .data = {{65, 5},
                                                                                                {35, 5},
                                                                                                {34, 20},
                                                                                                {36, 40}}};
    simple_bezier_font_table['f'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{35, 40},
                                                                                                {35, 100}}};
    simple_bezier_font_table['f'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{8,  40},
                                                                                                {50, 40}}};
}

void set_bezier_data_x() {
    simple_bezier_font_table['x'].size = 2;
    simple_bezier_font_table['x'].layers[0] = (simple_bezier_font_layer_t) {
            .size = 3,
            .data = {
                    10, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_FULL_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_FULL_Y
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
    simple_bezier_font_table['z'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 40},
                                                                                                {89, 40}}};
    simple_bezier_font_table['z'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 98},
                                                                                                {83, 44}}};
    simple_bezier_font_table['z'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{19, 98},
                                                                                                {87, 98}}};
}

void set_bezier_data_y() {
    simple_bezier_font_table['y'].size = 2;
    simple_bezier_font_table['y'].layers[0] = (simple_bezier_font_layer_t) {.size = 3, .data = {{28, 40},
                                                                                                {52, 103},
                                                                                                {66, 97}}};
    simple_bezier_font_table['y'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{91, 40},
                                                                                                {64, 103},
                                                                                                {55, 150},
                                                                                                {22, 140}}};
}

void set_bezier_data_p() {
    simple_bezier_font_table['p'].size = 2;
    simple_bezier_font_table['p'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{25, 40},
                                                                                                {25, 140}}};
    simple_bezier_font_table['p'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{27,  55},
                                                                                                {36,  30},
                                                                                                {82,  25},
                                                                                                {130, 40},
                                                                                                {126, 135},
                                                                                                {18,  123},
                                                                                                {26,  87},
                                                                                                {26,  67}}};
}

void set_bezier_data_s() {
    simple_bezier_font_table['s'].size = 1;
    simple_bezier_font_table['s'].layers[0] = (simple_bezier_font_layer_t) {.size = 10, .data = {{88,  51},
                                                                                                 {64,  27},
                                                                                                 {53,  22},
                                                                                                 {3,   51},
                                                                                                 {3,   135},
                                                                                                 {114, 3},
                                                                                                 {134, 76},
                                                                                                 {150, 115},
                                                                                                 {25,  114},
                                                                                                 {28,  76}}};
}

void set_bezier_data_v() {
    simple_bezier_font_table['v'].size = 2;
    simple_bezier_font_table['v'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{22, 40},
                                                                                                {53, 100}}};
    simple_bezier_font_table['v'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{54, 101},
                                                                                                {83, 39}}};
}

void set_bezier_data_g() {
    simple_bezier_font_table['g'].size = 2;
    simple_bezier_font_table['g'].layers[0] = (simple_bezier_font_layer_t) {.size = 6, .data = {{87,  40},
                                                                                                {87,  109},
                                                                                                {87,  115},
                                                                                                {131, 133},
                                                                                                {26,  151},
                                                                                                {20,  114}}};
    simple_bezier_font_table['g'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{87, 54},
                                                                                                {78, 17},
                                                                                                {8,  44},
                                                                                                {2,  44},
                                                                                                {4,  112},
                                                                                                {60, 111},
                                                                                                {82, 91},
                                                                                                {88, 68}}};
}