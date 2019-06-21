//
// Created by onureozcan on 14.06.2019.
//
#include <canvas.h>
#include <common.h>

#define CANVAS_BEZIER_CURVE_SAMPLING 100

void set_bezier_data_a();

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
}


// from osdev
void canvas_fill_rect(canvas_t *canvas, char *where, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w) {
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int t = j * canvas->depth;
            where[t] = r;
            where[t + 1] = g;
            where[t + 2] = b;
        }
        where += canvas->width * canvas->depth;
    }
}

// from osdev
void canvas_fill_rect_xy(canvas_t *canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t h, uint8_t w) {
    uint32_t where = x * canvas->depth + y * canvas->depth * canvas->width;
    canvas_fill_rect(canvas, canvas->buffer + where, r, g, b, h, w);
}

// from osdev
void canvas_put_pixel(canvas_t *canvas, int x, int y, uint8_t b, uint8_t g, uint8_t r) {
    if (x < 0 || x > canvas->width)
        return;
    if (y < 0 || y > canvas->height)
        return;
    // FIXME: what if the depth is of type 32 bits or 16 bits?
    uint32_t where = x * 3 + y * 3 * canvas->width;
    canvas->buffer[where] = b;
    canvas->buffer[where + 1] = g;
    canvas->buffer[where + 2] = r;
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
        canvas_fill_rect_xy(canvas, x, y, r, g, b, thickness, thickness);
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

static point_t canvas_get_interpolated_point(point_t p1, point_t p2, int percent) {
    point_t p;
    p.x = (p1.x + (float) percent / CANVAS_BEZIER_CURVE_SAMPLING * (p2.x - p1.x));
    p.y = (p1.y + (float) percent / CANVAS_BEZIER_CURVE_SAMPLING * (p2.y - p1.y));
    return p;
}

static point_t
canvas_draw_bezier_curve_internal(canvas_t *canvas, int x, int y, point_t points[], int size_of_points,
                                  uint8_t b, uint8_t g, uint8_t r, int percent) {
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
    for (int p = 0; p < CANVAS_BEZIER_CURVE_SAMPLING; p++) {
        point_t point = canvas_draw_bezier_curve_internal(canvas, x, y, points, size_of_points, b, g, r, p);
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
                                        round(CANVAS_SIMPLE_FONT_DEFAULT_THICKNESS * scale_x) + 1);
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
        }
    }
}