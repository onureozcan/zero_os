//
// Created by onureozcan on 14.06.2019.
//
#include <canvas.h>
#include <common.h>
#include <font_data.h>

#define CANVAS_BEZIER_CURVE_SAMPLING 100

static float canvas_area_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

static int canvas_is_point_inside_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);

void canvas_init() {
    // init font table
    set_bezier_data_a();
    set_bezier_data_b();
    set_bezier_data_c();
    set_bezier_data_d();
    set_bezier_data_e();
    set_bezier_data_t();
    set_bezier_data_h();
    set_bezier_data_l();
    set_bezier_data_q();
    set_bezier_data_u();
    set_bezier_data_i();
    set_bezier_data_r();
    set_bezier_data_k();
    set_bezier_data_o();
    set_bezier_data_w();
    set_bezier_data_n();
    set_bezier_data_f();
    set_bezier_data_x();
    set_bezier_data_j();
    set_bezier_data_m();
    set_bezier_data_z();
    set_bezier_data_Z();
    set_bezier_data_y();
    set_bezier_data_p();
    set_bezier_data_s();
    set_bezier_data_v();
    set_bezier_data_g();
    set_bezier_data_0();
    set_bezier_data_1();
    set_bezier_data_2();
    set_bezier_data_3();
    set_bezier_data_4();
    set_bezier_data_5();
    set_bezier_data_6();
    set_bezier_data_7();
    set_bezier_data_8();
    set_bezier_data_9();
    set_bezier_data_A();
    set_bezier_data_B();
    set_bezier_data_C();
    set_bezier_data_D();
    set_bezier_data_E();
    set_bezier_data_F();
    set_bezier_data_G();
    set_bezier_data_H();
    set_bezier_data_I();
    set_bezier_data_J();
    set_bezier_data_K();
    set_bezier_data_L();
    set_bezier_data_M();
    set_bezier_data_N();
    set_bezier_data_O();
    set_bezier_data_R();
    set_bezier_data_P();
    set_bezier_data_S();
    set_bezier_data_T();
    set_bezier_data_U();
    set_bezier_data_V();
    set_bezier_data_W();
    set_bezier_data_X();
    set_bezier_data_Y();
    set_bezier_data_Q();
    set_bezier_data_91();
    set_bezier_data_93();
    set_bezier_data_58();
    set_bezier_data_63();
    set_bezier_data_47();
    set_bezier_data_46();
}

void canvas_fill_triangle(canvas_t *canvas, int *coords, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    for (int i = 0; i < canvas->width; i++) {
        for (int j = 0; j < canvas->height; j++) {
            if (canvas_is_point_inside_triangle(
                    coords[0], coords[1],
                    coords[2], coords[3],
                    coords[4], coords[5],
                    i, j
            )) {
                canvas_put_pixel(canvas, i, j, r, g, b, a);
            }
        }
    }
}

// from osdev
void canvas_fill_rect(canvas_t *canvas, char *where, uint8_t r, uint8_t g, uint8_t b, uint32_t h, uint32_t w) {
    int i, j;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            int t = j * canvas->depth;
            where[t] = b;
            where[t + 1] = g;
            where[t + 2] = r;
            where[t + 3] = 0xff; // visibility byte
        }
        where += canvas->width * canvas->depth;
    }
}

// from osdev
void canvas_fill_rect_xy(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint32_t h, uint32_t w) {
    uint32_t where = x * canvas->depth + y * canvas->depth * canvas->width;
    canvas_fill_rect(canvas, canvas->buffer + where, r, g, b, h, w);
}

// from osdev
void canvas_put_pixel(canvas_t *canvas, int x, int y, uint8_t b, uint8_t g, uint8_t r, uint8_t alpha) {
    if (x < 0 || x > canvas->width)
        return;
    if (y < 0 || y > canvas->height)
        return;
    // FIXME: what if the depth is of type 16 bits?
    uint32_t where = x * canvas->depth + y * canvas->depth * canvas->width;
    canvas->buffer[where] = b;
    canvas->buffer[where + 1] = g;
    canvas->buffer[where + 2] = r;
    canvas->buffer[where + 3] = alpha; // ALPHA
}

void
canvas_draw_line(canvas_t *canvas, int x, int y, int x2, int y2, uint8_t r, uint8_t g, uint8_t b, uint32_t thickness) {
    int dx = (x2 - x), sx = x < x2 ? 1 : -1;
    int dy = (y2 - y), sy = y < y2 ? 1 : -1;
    if (dy < 0)
        dy = -dy;
    if (dx < 0)
        dx = -dx;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        canvas_fill_rect_xy(canvas, x, y, r, g, b, (uint8_t) (thickness * 1.5f), thickness);
        if (x == x2 && y == y2)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x += sx;
        }
        if (e2 < dy) {
            err += dx;
            y += sy;
        }
    }
}

static int canvas_is_point_inside_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) {
    float area_all = canvas_area_triangle(x1, y1, x2, y2, x3, y3);
    float area1 = canvas_area_triangle(x1, y1, x, y, x3, y3);
    float area2 = canvas_area_triangle(x, y, x2, y2, x3, y3);
    float area3 = canvas_area_triangle(x1, y1, x2, y2, x, y);
    return (area_all == area1 + area2 + area3);
}

float canvas_area_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    float area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f;
    if (area < 0) {
        area = -area;
    }
    return area;
}

static point_t canvas_get_interpolated_point(point_t p1, point_t p2, float percent) {
    point_t p;
    p.x = (p1.x + percent / 100 * (p2.x - p1.x));
    p.y = (p1.y + percent / 100 * (p2.y - p1.y));
    return p;
}

static point_t
canvas_draw_bezier_curve_internal(canvas_t *canvas, int x, int y, point_t points[], int size_of_points,
                                  uint8_t b, uint8_t g, uint8_t r, float percent) {
    if (size_of_points == 2) {
        return canvas_get_interpolated_point(points[0], points[1], percent);
    }
    point_t new_points[CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS];
    int new_size = 0;
    for (int i = 0; i < size_of_points - 1; i++) {
        point_t current = points[i];
        point_t next = points[i + 1];
        point_t new_point = canvas_get_interpolated_point(current, next, percent);
        new_points[new_size++] = new_point;
    }
    return canvas_draw_bezier_curve_internal(canvas, x, y, new_points, new_size, b, g, r, percent);
}

static int round(float f) {
    if (f < .5f) {
        return (int) (f - .5f);
    }
    return (int) (f + .5f);
}

static void
canvas_draw_bezier_curve_scaled(canvas_t *canvas, int x, int y, point_t points[], int size_of_points, uint8_t b,
                                uint8_t g,
                                uint8_t r, float scale_x, float scale_y, uint32_t thickness) {
    point_t prev_point;
    for (int p = 0; p < CANVAS_BEZIER_CURVE_SAMPLING + 1; p++) {
        point_t point = canvas_draw_bezier_curve_internal(canvas, x, y, points, size_of_points, b, g, r,
                                                          ((float) p * 100) / CANVAS_BEZIER_CURVE_SAMPLING);
        if (p != 0)
            canvas_draw_line(canvas, round(point.x * scale_x + x), round(point.y * scale_y + y),
                             round(prev_point.x * scale_x + x), round(prev_point.y * scale_y + y),
                             r, g, b, thickness);
        prev_point = point;
    }
}

void
canvas_draw_bezier_curve(canvas_t *canvas, int x, int y, point_t points[], int size_of_points, uint8_t b, uint8_t g,
                         uint8_t r, uint32_t thickness) {
    canvas_draw_bezier_curve_scaled(canvas, x, y, points, size_of_points, b, g, r, 1, 1, thickness);

}

void canvas_draw_char(canvas_t *canvas, int c, int x, int y, uint8_t r, uint8_t g, uint8_t b,
                      uint32_t h, uint32_t w,
                      uint32_t thickness) {
    simple_bezier_font_t glyph = simple_bezier_font_table[c];
    for (int l = 0; l < glyph.size; l++) {
        float scale_x = w / (float) (CANVAS_SIMPLE_FONT_DEFAULT_SIZE_X);
        canvas_draw_bezier_curve_scaled(canvas, x, y, (point_t *) &glyph.layers[l].data, glyph.layers[l].size,
                                        b, g, r, scale_x,
                                        h / (float) (CANVAS_SIMPLE_FONT_DEFAULT_SIZE_Y),
                                        thickness);
    }
}

static uint8_t *canvas_get_pixel_xy(canvas_t *canvas, int x, int y) {
    return (uint8_t *) &canvas->buffer[canvas->depth * canvas->width * y + x * canvas->depth];
}

void canvas_blur_xy(canvas_t *canvas, int i, int j, int h, int w, int mult) {
    for (int x = i; x < w; x++) {
        for (int y = j; y < h; y++) {
            uint8_t *pixel_00 = canvas_get_pixel_xy(canvas, x - 1, y - 1);
            uint8_t *pixel_01 = canvas_get_pixel_xy(canvas, x - 1, y);
            uint8_t *pixel_02 = canvas_get_pixel_xy(canvas, x - 1, y + 1);
            uint8_t *pixel_10 = canvas_get_pixel_xy(canvas, x, y - 1);
            uint8_t *pixel_11 = canvas_get_pixel_xy(canvas, x, y);
            uint8_t *pixel_12 = canvas_get_pixel_xy(canvas, x, y + 1);
            uint8_t *pixel_20 = canvas_get_pixel_xy(canvas, x + 1, y - 1);
            uint8_t *pixel_21 = canvas_get_pixel_xy(canvas, x + 1, y);
            uint8_t *pixel_22 = canvas_get_pixel_xy(canvas, x + 1, y + 1);
            pixel_11[0] = (pixel_00[0] + pixel_01[0] + pixel_02[0]
                           + pixel_10[0] + pixel_11[0] * mult + pixel_12[0]
                           + pixel_20[0] + pixel_21[0] + pixel_22[0]) / (8 + mult);
            pixel_11[1] = (pixel_00[1] + pixel_01[1] + pixel_02[1]
                           + pixel_10[1] + pixel_11[1] * mult + pixel_12[1]
                           + pixel_20[1] + pixel_21[1] + pixel_22[1]) / (8 + mult);
            pixel_11[2] = (pixel_00[2] + pixel_01[2] + pixel_02[2]
                           + pixel_10[2] + pixel_11[2] * mult + pixel_12[2]
                           + pixel_20[2] + pixel_21[2] + pixel_22[2]) / (8 + mult);
            pixel_11[3] = (pixel_00[3] + pixel_01[3] + pixel_02[3]
                           + pixel_10[3] + pixel_11[3] * mult + pixel_12[3]
                           + pixel_20[3] + pixel_21[3] + pixel_22[3]) / (8 + mult);
        }
    }
}
