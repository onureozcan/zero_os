//
// Created by onureozcan on 14.06.2019.
//
#include <canvas.h>


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
        canvas_fill_rect_xy(canvas, x, y, b, g, r, thickness, thickness);
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
    p.x = (int) (p1.x + percent / 100.0f * (p2.x - p1.x));
    p.y = (int) (p1.y + percent / 100.0f * (p2.y - p1.y));
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

void
canvas_draw_bezier_curve(canvas_t *canvas, int x, int y, point_t points[], int size_of_points, uint8_t b, uint8_t g,
                         uint8_t r, uint32_t thickness) {
    point_t prev_point;
    for (int p = 0; p < 101; p++) {
        point_t point = canvas_draw_bezier_curve_internal(canvas, x, y, points, size_of_points, b, g, r, p);
        if (p != 0)
            canvas_draw_line(canvas, point.x, point.y, prev_point.x, prev_point.y, r, g, b, thickness);
        prev_point = point;
    }
}