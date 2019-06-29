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
    simple_bezier_font_table['b'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{27, 2},
                                                                                                {27, 100}}};
    simple_bezier_font_table['b'].layers[1] = (simple_bezier_font_layer_t) {.size = 9, .data = {{27,  48},
                                                                                                {61,  17},
                                                                                                {110, 44},
                                                                                                {100, 88},
                                                                                                {87,  100},
                                                                                                {71,  100},
                                                                                                {50,  100},
                                                                                                {35,  100},
                                                                                                {27,  92}}};
}

void set_bezier_data_c() {
    simple_bezier_font_table['c'].size = 1;
    simple_bezier_font_table['c'].layers[0] = (simple_bezier_font_layer_t) {.size = 6, .data = {{85,  50},
                                                                                                {65,  25},
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
                    90, 100
            }
    };
    simple_bezier_font_table['d'].layers[1] = (simple_bezier_font_layer_t) {
            .size = 4,
            .data = {
                    90, 50,
                    0, 10,
                    0, 130,
                    90, 95
            }
    };
}

void set_bezier_data_e() {
    simple_bezier_font_table['e'].size = 2;
    simple_bezier_font_table['e'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{36 - 10, 61},
                                                                                                {99 - 10, 61}}};
    simple_bezier_font_table['e'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{98 - 10,  61},
                                                                                                {93 - 10,  37},
                                                                                                {80 - 10,  27},
                                                                                                {12 - 10,  27},
                                                                                                {-1 - 10,  72},
                                                                                                {31 - 10,  109 - 5},
                                                                                                {61 - 10,  115 - 5},
                                                                                                {103 - 15, 90 - 5}}};
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
                    BEZIER_FONT_HALF_X - 20, BEZIER_FONT_HALF_Y,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y - 10,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_HALF_Y - 10,
                    BEZIER_FONT_FULL_X - 10, BEZIER_FONT_FULL_Y
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
                                                                                                {69,  20},
                                                                                                {100, 25},
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
    simple_bezier_font_table['i'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{40, 40},
                                                                                                {70, 40}}};
    simple_bezier_font_table['i'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{60, 40},
                                                                                                {60, 100}}};
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
    simple_bezier_font_table['o'].layers[0] = (simple_bezier_font_layer_t) {.size = 9, .data = {{50,  100},
                                                                                                {100, 105},
                                                                                                {100, 55},
                                                                                                {100, 30},
                                                                                                {50,  20},
                                                                                                {0,   30},
                                                                                                {0,   55},
                                                                                                {0,   105},
                                                                                                {56,  100}}};
}


void set_bezier_data_m() {
    simple_bezier_font_table['m'].size = 3;
    simple_bezier_font_table['m'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{10, 100},
                                                                                                {10, 40}}};
    simple_bezier_font_table['m'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{10, 50},
                                                                                                {44, 24},
                                                                                                {50, 30},
                                                                                                {50, 100}}};
    simple_bezier_font_table['m'].layers[2] = (simple_bezier_font_layer_t) {.size = 4, .data = {{50, 50},
                                                                                                {90, 18},
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
    simple_bezier_font_table['f'].layers[0] = (simple_bezier_font_layer_t) {.size = 4, .data = {{75, 5},
                                                                                                {45, 5},
                                                                                                {44, 20},
                                                                                                {46, 40}}};
    simple_bezier_font_table['f'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{45, 40},
                                                                                                {45, 100}}};
    simple_bezier_font_table['f'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20,  40},
                                                                                                {80, 40}}};
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
                    BEZIER_FONT_FULL_X, 0,
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
                                                                                                 {104, 3},
                                                                                                 {114, 76},
                                                                                                 {140, 115},
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

void set_bezier_data_0() {
    simple_bezier_font_table['0'].size = 1;
    simple_bezier_font_table['0'].layers[0] = (simple_bezier_font_layer_t) {.size = 7, .data = {{50,  0},
                                                                                                {100, 0},
                                                                                                {100, 130},
                                                                                                {50,  130},
                                                                                                {0,   130},
                                                                                                {0,   0},
                                                                                                {53,  0}}};
}

void set_bezier_data_1() {
    simple_bezier_font_table['1'].size = 3;
    simple_bezier_font_table['1'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{33, 100},
                                                                                                {71, 100}}};
    simple_bezier_font_table['1'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{54, 100},
                                                                                                {54, 0}}};
    simple_bezier_font_table['1'].layers[2] = (simple_bezier_font_layer_t) {.size = 3, .data = {{54, 0},
                                                                                                {51, 15},
                                                                                                {38, 20}}};
}

void set_bezier_data_2() {
    simple_bezier_font_table['2'].size = 2;
    simple_bezier_font_table['2'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{82, 100},
                                                                                                {20, 100}}};
    simple_bezier_font_table['2'].layers[1] = (simple_bezier_font_layer_t) {.size = 5, .data = {{22,  100},
                                                                                                {102, 44},
                                                                                                {94,  17},
                                                                                                {68,  -9},
                                                                                                {31,  7}}};
}

void set_bezier_data_3() {
    simple_bezier_font_table['3'].size = 2;
    simple_bezier_font_table['3'].layers[0] = (simple_bezier_font_layer_t) {.size = 5, .data = {{18, 90},
                                                                                                {60, 112},
                                                                                                {93, 95},
                                                                                                {94, 58},
                                                                                                {60, 47}}};
    simple_bezier_font_table['3'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{60, 48},
                                                                                                {97, 29},
                                                                                                {67, -8},
                                                                                                {34, 6}}};
}


void set_bezier_data_4() {
    simple_bezier_font_table['4'].size = 3;
    simple_bezier_font_table['4'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{71, 100},
                                                                                                {71, 00}}};
    simple_bezier_font_table['4'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{70, 0},
                                                                                                {21, 66}}};
    simple_bezier_font_table['4'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{22, 66},
                                                                                                {86, 66}}};
}

void set_bezier_data_5() {
    simple_bezier_font_table['5'].size = 3;
    simple_bezier_font_table['5'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{82, 4},
                                                                                                {22, 4}}};
    simple_bezier_font_table['5'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{22, 5},
                                                                                                {22, 50}}};
    simple_bezier_font_table['5'].layers[2] = (simple_bezier_font_layer_t) {.size = 5, .data = {{23,  50},
                                                                                                {82,  24},
                                                                                                {109, 60},
                                                                                                {84,  132},
                                                                                                {21,  93}}};
}

void set_bezier_data_6() {
    simple_bezier_font_table['6'].size = 2;
    simple_bezier_font_table['6'].layers[0] = (simple_bezier_font_layer_t) {.size = 6, .data = {{56, 100},
                                                                                                {8,  100},
                                                                                                {12, 68},
                                                                                                {22, -1},
                                                                                                {34, 0},
                                                                                                {76, 0}}};
    simple_bezier_font_table['6'].layers[1] = (simple_bezier_font_layer_t) {.size = 7, .data = {{54,  100},
                                                                                                {88,  100},
                                                                                                {105, 76},
                                                                                                {69,  39},
                                                                                                {94,  34},
                                                                                                {36,  37},
                                                                                                {31,  48}}};
}

void set_bezier_data_7() {
    simple_bezier_font_table['7'].size = 3;
    simple_bezier_font_table['7'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{22, 4},
                                                                                                {88, 4}}};
    simple_bezier_font_table['7'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{87, 5},
                                                                                                {87, 23}}};
    simple_bezier_font_table['7'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{87, 22},
                                                                                                {43, 100}}};
}

void set_bezier_data_8() {
    simple_bezier_font_table['8'].size = 3;
    simple_bezier_font_table['8'].layers[0] = (simple_bezier_font_layer_t) {.size = 4, .data = {{52, 1},
                                                                                                {92, 1},
                                                                                                {84, 34},
                                                                                                {56, 51}}};
    simple_bezier_font_table['8'].layers[1] = (simple_bezier_font_layer_t) {.size = 8, .data = {{52,  0},
                                                                                                {15,  1},
                                                                                                {10,  30},
                                                                                                {26,  61},
                                                                                                {120, 56},
                                                                                                {92,  87},
                                                                                                {82,  117},
                                                                                                {26,  95}}};
    simple_bezier_font_table['8'].layers[2] = (simple_bezier_font_layer_t) {.size = 4, .data = {{33, 98},
                                                                                                {5,  85},
                                                                                                {27, 55},
                                                                                                {48, 48}}};
}

void set_bezier_data_9() {
    simple_bezier_font_table['9'].size = 2;
    simple_bezier_font_table['9'].layers[0] = (simple_bezier_font_layer_t) {.size = 6, .data = {{75, 56},
                                                                                                {5,  81},
                                                                                                {2,  27},
                                                                                                {4,  -6},
                                                                                                {62, -8},
                                                                                                {76, 22}}};
    simple_bezier_font_table['9'].layers[1] = (simple_bezier_font_layer_t) {.size = 5, .data = {{76, 19},
                                                                                                {85, 60},
                                                                                                {98, 91},
                                                                                                {49, 118},
                                                                                                {16, 98}}};
}

void set_bezier_data_A() {
    simple_bezier_font_table['A'].size = 3;
    simple_bezier_font_table['A'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{7,  100},
                                                                                                {50, 1}}};
    simple_bezier_font_table['A'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{50, 4},
                                                                                                {92, 103}}};
    simple_bezier_font_table['A'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{29, 55},
                                                                                                {70, 55}}};
}

void set_bezier_data_B() {
    simple_bezier_font_table['B'].size = 3;
    simple_bezier_font_table['B'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{24, 100},
                                                                                                {24, 0}}};
    simple_bezier_font_table['B'].layers[1] = (simple_bezier_font_layer_t) {.size = 5, .data = {{25, 0},
                                                                                                {85, 0},
                                                                                                {81, 30},
                                                                                                {82, 48},
                                                                                                {33, 48}}};
    simple_bezier_font_table['B'].layers[2] = (simple_bezier_font_layer_t) {.size = 5, .data = {{32, 49},
                                                                                                {97, 44},
                                                                                                {87, 84},
                                                                                                {92, 100},
                                                                                                {23, 100}}};
}

void set_bezier_data_C() {
    simple_bezier_font_table['C'].size = 1;
    simple_bezier_font_table['C'].layers[0] = (simple_bezier_font_layer_t) {.size = 7, .data = {{90, 20},
                                                                                                {44, -21},
                                                                                                {7,  20},
                                                                                                {0,  49},
                                                                                                {4,  100},
                                                                                                {44, 126},
                                                                                                {92, 89}}};
}

void set_bezier_data_D() {
    simple_bezier_font_table['D'].size = 2;
    simple_bezier_font_table['D'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{16, 100},
                                                                                                {16, 1}}};
    simple_bezier_font_table['D'].layers[1] = (simple_bezier_font_layer_t) {.size = 5, .data = {{16,  2},
                                                                                                {102, -4},
                                                                                                {90,  55},
                                                                                                {106, 99},
                                                                                                {17,  99}}};
}

void set_bezier_data_E() {
    simple_bezier_font_table['E'].size = 4;
    simple_bezier_font_table['E'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{26, 1},
                                                                                                {26, 99}}};
    simple_bezier_font_table['E'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{25, 2},
                                                                                                {86, 2}}};
    simple_bezier_font_table['E'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{26, 48},
                                                                                                {77, 48}}};
    simple_bezier_font_table['E'].layers[3] = (simple_bezier_font_layer_t) {.size = 2, .data = {{26, 100},
                                                                                                {86, 100}}};
}

void set_bezier_data_F() {
    simple_bezier_font_table['F'].size = 3;
    simple_bezier_font_table['F'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{30, 100},
                                                                                                {30, 0}}};
    simple_bezier_font_table['F'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{30, 48},
                                                                                                {76, 48}}};
    simple_bezier_font_table['F'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{29, 0},
                                                                                                {89, 0}}};
}

void set_bezier_data_G() {
    simple_bezier_font_table['G'].size = 5;
    simple_bezier_font_table['G'].layers[0] = (simple_bezier_font_layer_t) {.size = 3, .data = {{89, 12},
                                                                                                {77, 2},
                                                                                                {50, 2}}};
    simple_bezier_font_table['G'].layers[1] = (simple_bezier_font_layer_t) {.size = 5, .data = {{52, 2},
                                                                                                {5,  1},
                                                                                                {-1, 54},
                                                                                                {0,  97},
                                                                                                {56, 100}}};
    simple_bezier_font_table['G'].layers[2] = (simple_bezier_font_layer_t) {.size = 3, .data = {{54, 100},
                                                                                                {89, 99},
                                                                                                {93, 87}}};
    simple_bezier_font_table['G'].layers[3] = (simple_bezier_font_layer_t) {.size = 2, .data = {{93, 87},
                                                                                                {93, 53}}};
    simple_bezier_font_table['G'].layers[4] = (simple_bezier_font_layer_t) {.size = 2, .data = {{94, 55},
                                                                                                {48, 55}}};
}

void set_bezier_data_H() {
    simple_bezier_font_table['H'].size = 3;
    simple_bezier_font_table['H'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 100},
                                                                                                {20, 1}}};
    simple_bezier_font_table['H'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{90, 100},
                                                                                                {90, 0}}};
    simple_bezier_font_table['H'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 49},
                                                                                                {89, 49}}};
}

void set_bezier_data_I() {
    simple_bezier_font_table['I'].size = 3;
    simple_bezier_font_table['I'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{34, 1},
                                                                                                {78, 1}}};
    simple_bezier_font_table['I'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{34, 100},
                                                                                                {78, 100}}};
    simple_bezier_font_table['I'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{56, 100},
                                                                                                {56, 1}}};
}

void set_bezier_data_J() {
    simple_bezier_font_table['J'].size = 2;
    simple_bezier_font_table['J'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{34, 1},
                                                                                                {78, 1}}};
    simple_bezier_font_table['J'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{66, 1},
                                                                                                {66, 100},
                                                                                                {66, 100},
                                                                                                {25, 99}}};
}

void set_bezier_data_K() {
    simple_bezier_font_table['K'].size = 3;
    simple_bezier_font_table['K'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{26, 0},
                                                                                                {26, 100}}};
    simple_bezier_font_table['K'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{26, 65},
                                                                                                {80, 0}}};
    simple_bezier_font_table['K'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{37, 52},
                                                                                                {82, 100}}};
}

void set_bezier_data_L() {
    simple_bezier_font_table['L'].size = 2;
    simple_bezier_font_table['L'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{32, 100},
                                                                                                {32, 0}}};
    simple_bezier_font_table['L'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{32, 100},
                                                                                                {88, 100}}};
}

void set_bezier_data_M() {
    simple_bezier_font_table['M'].size = 4;
    simple_bezier_font_table['M'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{10, 100},
                                                                                                {10, 0}}};
    simple_bezier_font_table['M'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{10, 0},
                                                                                                {49, 75}}};
    simple_bezier_font_table['M'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{49, 75},
                                                                                                {88, 0}}};
    simple_bezier_font_table['M'].layers[3] = (simple_bezier_font_layer_t) {.size = 2, .data = {{88, 0},
                                                                                                {88, 100}}};
}

void set_bezier_data_N() {
    simple_bezier_font_table['N'].size = 3;
    simple_bezier_font_table['N'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 100},
                                                                                                {20, 0}}};
    simple_bezier_font_table['N'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{20, 1},
                                                                                                {84, 100}}};
    simple_bezier_font_table['N'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{83, 99},
                                                                                                {83, 0}}};
}

void set_bezier_data_R() {
    simple_bezier_font_table['R'].size = 3;
    simple_bezier_font_table['R'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{24, 0},
                                                                                                {24, 100}}};
    simple_bezier_font_table['R'].layers[1] = (simple_bezier_font_layer_t) {.size = 6, .data = {{24, 1},
                                                                                                {85, 0},
                                                                                                {71, 6},
                                                                                                {78, 54},
                                                                                                {74, 56},
                                                                                                {24, 54}}};
    simple_bezier_font_table['R'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{46, 54},
                                                                                                {86, 102}}};
}

void set_bezier_data_O() {
    simple_bezier_font_table['O'].size = 4;
    simple_bezier_font_table['O'].layers[0] = (simple_bezier_font_layer_t) {.size = 3, .data = {{49, 100},
                                                                                                {90, 100},
                                                                                                {90, 50}}};
    simple_bezier_font_table['O'].layers[1] = (simple_bezier_font_layer_t) {.size = 3, .data = {{90, 51},
                                                                                                {90, 0},
                                                                                                {50, 0}}};
    simple_bezier_font_table['O'].layers[2] = (simple_bezier_font_layer_t) {.size = 3, .data = {{51, 0},
                                                                                                {10, 0},
                                                                                                {10, 50}}};
    simple_bezier_font_table['O'].layers[3] = (simple_bezier_font_layer_t) {.size = 3, .data = {{10, 50},
                                                                                                {10, 100},
                                                                                                {50, 100}}};
}

void set_bezier_data_P() {
    simple_bezier_font_table['P'].size = 3;
    simple_bezier_font_table['P'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{28, 100},
                                                                                                {28, 0}}};
    simple_bezier_font_table['P'].layers[1] = (simple_bezier_font_layer_t) {.size = 3, .data = {{27, 0},
                                                                                                {80, -3},
                                                                                                {84, 28}}};
    simple_bezier_font_table['P'].layers[2] = (simple_bezier_font_layer_t) {.size = 3, .data = {{84, 28},
                                                                                                {84, 61},
                                                                                                {29, 56}}};
}

void set_bezier_data_S() {
    simple_bezier_font_table['S'].size = 2;
    simple_bezier_font_table['S'].layers[0] = (simple_bezier_font_layer_t) {.size = 5, .data = {{81, 5},
                                                                                                {21, -17},
                                                                                                {2,  22},
                                                                                                {13, 46},
                                                                                                {42, 47}}};
    simple_bezier_font_table['S'].layers[1] = (simple_bezier_font_layer_t) {.size = 5, .data = {{40,  47},
                                                                                                {118, 52},
                                                                                                {86,  86},
                                                                                                {96,  111},
                                                                                                {13,  99}}};
}

void set_bezier_data_T() {
    simple_bezier_font_table['T'].size = 2;
    simple_bezier_font_table['T'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{8,  0},
                                                                                                {91, 0}}};
    simple_bezier_font_table['T'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{48, 1},
                                                                                                {48, 100}}};
}

void set_bezier_data_U() {
    simple_bezier_font_table['U'].size = 2;
    simple_bezier_font_table['U'].layers[0] = (simple_bezier_font_layer_t) {.size = 4, .data = {{16, 0},
                                                                                                {16, 90},
                                                                                                {16, 100},
                                                                                                {50, 100}}};
    simple_bezier_font_table['U'].layers[1] = (simple_bezier_font_layer_t) {.size = 4, .data = {{84, 0},
                                                                                                {84, 90},
                                                                                                {84, 100},
                                                                                                {48, 100}}};
}

void set_bezier_data_V() {
    simple_bezier_font_table['V'].size = 2;
    simple_bezier_font_table['V'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{21, 0},
                                                                                                {50, 100}}};
    simple_bezier_font_table['V'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{50, 100},
                                                                                                {81, 0}}};
}

void set_bezier_data_W() {
    simple_bezier_font_table['W'].size = 4;
    simple_bezier_font_table['W'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{10, 0},
                                                                                                {33, 100}}};
    simple_bezier_font_table['W'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{33, 100},
                                                                                                {50, 21}}};
    simple_bezier_font_table['W'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{50, 23},
                                                                                                {66, 100}}};
    simple_bezier_font_table['W'].layers[3] = (simple_bezier_font_layer_t) {.size = 2, .data = {{66, 99},
                                                                                                {89, 1}}};
}

void set_bezier_data_X() {
    simple_bezier_font_table['X'].size = 2;
    simple_bezier_font_table['X'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{11, 0},
                                                                                                {89, 100}}};
    simple_bezier_font_table['X'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{90, 1},
                                                                                                {11, 99}}};
}

void set_bezier_data_Y() {
    simple_bezier_font_table['Y'].size = 3;
    simple_bezier_font_table['Y'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{14, 0},
                                                                                                {49, 50}}};
    simple_bezier_font_table['Y'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{85, 0},
                                                                                                {49, 50}}};
    simple_bezier_font_table['Y'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{49, 49},
                                                                                                {49, 100}}};
}

void set_bezier_data_Q() {
    simple_bezier_font_table['Q'].size = 5;
    simple_bezier_font_table['Q'].layers[0] = (simple_bezier_font_layer_t) {.size = 3, .data = {{49, 100},
                                                                                                {90, 100},
                                                                                                {90, 50}}};
    simple_bezier_font_table['Q'].layers[1] = (simple_bezier_font_layer_t) {.size = 3, .data = {{90, 51},
                                                                                                {90, 0},
                                                                                                {50, 0}}};
    simple_bezier_font_table['Q'].layers[2] = (simple_bezier_font_layer_t) {.size = 3, .data = {{51, 0},
                                                                                                {10, 0},
                                                                                                {10, 50}}};
    simple_bezier_font_table['Q'].layers[3] = (simple_bezier_font_layer_t) {.size = 3, .data = {{10, 50},
                                                                                                {10, 100},
                                                                                                {50, 100}}};
    simple_bezier_font_table['Q'].layers[4] = (simple_bezier_font_layer_t) {.size = 2, .data = {
            {70, 70},
            {90, 90}
    }};
}

void set_bezier_data_91() {
    simple_bezier_font_table['['].size = 3;
    simple_bezier_font_table['['].layers[0] = (simple_bezier_font_layer_t) {
            .size = 2, .data = {{67, 0},
                                {33, 0}}
    };
    simple_bezier_font_table['['].layers[1] = (simple_bezier_font_layer_t) {
            .size = 2, .data = {{34, 100},
                                {34, 1}}
    };
    simple_bezier_font_table['['].layers[2] = (simple_bezier_font_layer_t) {
            .size = 2, .data = {{34, 100},
                                {67, 100}}
    };
}

void set_bezier_data_93() {
    simple_bezier_font_table[']'].size = 3;
    simple_bezier_font_table[']'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{32, 100},
                                                                                                {66, 100}}};
    simple_bezier_font_table[']'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{67, 100},
                                                                                                {67, 0}}};
    simple_bezier_font_table[']'].layers[2] = (simple_bezier_font_layer_t) {.size = 2, .data = {{66, 0},
                                                                                                {32, 0}}};
}

void set_bezier_data_58() {
    simple_bezier_font_table[':'].size = 2;
    simple_bezier_font_table[':'].layers[0] = (simple_bezier_font_layer_t) {.size = 2, .data = {{46, 31},
                                                                                                {55, 31}}};
    simple_bezier_font_table[':'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{46, 86},
                                                                                                {55, 86}}};
}

void set_bezier_data_63() {
    simple_bezier_font_table['?'].size = 2;
    simple_bezier_font_table['?'].layers[0] = (simple_bezier_font_layer_t) {.size = 7, .data = {{26,  3},
                                                                                                {76,  -16},
                                                                                                {89,  15},
                                                                                                {104, 40},
                                                                                                {71,  46},
                                                                                                {44,  39},
                                                                                                {46,  78}}};
    simple_bezier_font_table['?'].layers[1] = (simple_bezier_font_layer_t) {.size = 2, .data = {{45, 86},
                                                                                                {45, 100}}};
}