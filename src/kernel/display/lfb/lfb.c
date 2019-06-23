//
// Created by onureozcan on 08.06.2019.
//

#include <memory/memory_manager.h>
#include <display/lfb.h>
#include <string/k_string.h>
#include <display/console.h>
#include <canvas.h>
#include <common.h>

static int lfb_width;
static int lfb_height;
static char *framebuffer;
static char back_buffer[LFB_MAX_SUPPORTED_HEIGHT * LFB_MAX_SUPPORTED_WIDTH * LFB_DEPTH_BYTES];
static int buffer_size;
static int char_width_pixels;
static int char_height_pixels;
static int char_pos;
static int bkg_color = 0;
static int lfb_available = FALSE;
// are caches initialized?
static int caches_available;
// a map to cache rendered font data.
// keys are chars and values are buffer to them.
// each buffer is of width char_width_pixels and
// of height char_height_pixels
static uint8_t **font_cache_map;

#define LFB_SCREEN_PADDING_X 200
#define LFB_SCREEN_PADDING_Y 5
#define LFB_LINE_SPACING_X 1
#define LFB_LINE_SPACING_Y 2
#define LFB_CHAR_THICKNESS 2

#define CHAR_COLOR_R 200
#define CHAR_COLOR_G 200
#define CHAR_COLOR_B 200

#define LFB_USE_CACHE

canvas_t canvas;
uint8_t *aa_atlas;

/***********STATIC METHODS***********/

static uint8_t *lfb_cache_char_alpha_map(int c, int w, int h);

/**
 * this function initializes font caches.
 */
static void init_font_cache_data() {
    lfb_available = FALSE;
    int aa_atlas_size = char_width_pixels * char_height_pixels * LFB_DEPTH_BYTES * 4;
    aa_atlas = (uint8_t *) k_malloc(aa_atlas_size);
    memset(aa_atlas, 0, aa_atlas_size);
    font_cache_map = (uint8_t **) k_malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++) {
        font_cache_map[i] = lfb_cache_char_alpha_map(i, char_width_pixels, char_height_pixels);
    }
    lfb_available = TRUE;
}

/**
 * this function renders given char to a clean black buffer.
 * then caches it in font_cache_map.
 * if there is already a cached data, will reuse it.
 * @param c char to render.
 * @return rendered buffer.
 */
static uint8_t *lfb_cache_char_alpha_map(int c, int w, int h) {
    if (font_cache_map[c] == NULL) {
        // not rendered and cached
        font_cache_map[c] = (char *) k_malloc(w * h * LFB_DEPTH_BYTES);
        canvas_t temp_canvas;
        temp_canvas.height = h * 2;
        temp_canvas.width = w * 2;
        temp_canvas.depth = LFB_DEPTH_BYTES;
        temp_canvas.buffer = aa_atlas;
        memset(temp_canvas.buffer, 0, h * 2 * w * 2 * LFB_DEPTH_BYTES);
        canvas_draw_char(&temp_canvas, c, 1, 1, CHAR_COLOR_R, CHAR_COLOR_G, CHAR_COLOR_B,
                         temp_canvas.height - 1 - LFB_LINE_SPACING_Y,
                         temp_canvas.width - 1 - LFB_LINE_SPACING_X, LFB_CHAR_THICKNESS);
        for (int j = 0; j < temp_canvas.height; j += 2) {
            for (int i = 0; i < temp_canvas.width; i += 2) {
                uint8_t *big00 = aa_atlas + (i * LFB_DEPTH_BYTES + j * LFB_DEPTH_BYTES * temp_canvas.width);
                uint8_t *big01 = aa_atlas + (i * LFB_DEPTH_BYTES + (j + 1) * LFB_DEPTH_BYTES * temp_canvas.width);
                uint8_t *big10 = aa_atlas + ((i + 1) * LFB_DEPTH_BYTES + j * LFB_DEPTH_BYTES * temp_canvas.width);
                uint8_t *big11 = aa_atlas + ((i + 1) * LFB_DEPTH_BYTES + (j + 1) * LFB_DEPTH_BYTES * temp_canvas.width);
                uint8_t *small =
                        font_cache_map[c] + (i / 2 * LFB_DEPTH_BYTES + j / 2 * LFB_DEPTH_BYTES * w);
                *small = (*big00 + *big01 + *big10 + *big11) / 4;
                small[1] = (big00[1] + big01[1] + big10[1] + big11[1]) / 4;
                small[2] = (big00[2] + big01[2] + big10[2] + big11[2]) / 4;
            }
        }
    }
    return font_cache_map[c];
}

/**
 * blends a given buffer to the back buffer by using addition method.
 * @param x x coord to blend.
 * @param y y coord to blend.
 * @param width width of the buffer.
 * @param height height of the buffer.
 * @param data the buffer.
 */
static void lfb_blend_addition(int x, int y, int width, int height, char *data) {
    char *where = back_buffer + (x * LFB_DEPTH_BYTES + y * LFB_DEPTH_BYTES * lfb_width);
    char *where_data = data;
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int t = j * LFB_DEPTH_BYTES;
            where[t] = where_data[t];
            where[t + 1] = where_data[t + 1];
            where[t + 2] = where_data[t + 2];
        }
        where += LFB_DEPTH_BYTES * lfb_width;
        where_data += LFB_DEPTH_BYTES * width;
    }
}

/***********API METHODS***********/
void lfb_set_malloc_available() {
#ifdef LFB_USE_CACHE
    init_font_cache_data();
    caches_available = TRUE;
#endif
}

void lfb_init(int height, int width, void *lfb_buffer) {
    lfb_width = width;
    lfb_height = height;
    framebuffer = (char *) lfb_buffer;
    buffer_size = lfb_width * lfb_height * LFB_DEPTH_BYTES;
    lfb_clear();
    char_height_pixels = (height - LFB_SCREEN_PADDING_Y) / KERNEL_CONSOLE_HEIGHT;
    char_width_pixels = (width - LFB_SCREEN_PADDING_X) / KERNEL_CONSOLE_WIDTH;
    canvas_init();
    canvas.depth = LFB_DEPTH_BYTES;
    canvas.buffer = back_buffer;
    canvas.height = height;
    canvas.width = width;
}

void lfb_put_char(char c) {
    char_pos++;
    char_pos %= (KERNEL_CONSOLE_BUFFER_SIZE);
    if (!lfb_available) return;
    int col = char_pos / KERNEL_CONSOLE_WIDTH;
    int row = char_pos - col * KERNEL_CONSOLE_WIDTH;

    int x = row * char_width_pixels + (LFB_SCREEN_PADDING_X / 2);
    int y = col * char_height_pixels + (LFB_SCREEN_PADDING_Y);
    int h = char_height_pixels - LFB_LINE_SPACING_Y;
    int w = char_width_pixels - LFB_LINE_SPACING_X;

#ifdef LFB_USE_CACHE
    if (!caches_available) {
// slow path
#endif
        canvas_draw_char(&canvas, c, x, y, CHAR_COLOR_R, CHAR_COLOR_G, CHAR_COLOR_B, h, w, LFB_CHAR_THICKNESS);
#ifdef LFB_USE_CACHE
    } else {
        // use pre-rendered chars
        char *font_alpha_data = font_cache_map[c];
        lfb_blend_addition(x, y, char_width_pixels, char_height_pixels, font_alpha_data);

    }
#endif

}

void lfb_clear() {
    if (!lfb_available) return;
    memset(back_buffer, bkg_color, buffer_size);
}

void lfb_repaint() {
    if (!lfb_available) return;
    memcpy(framebuffer, back_buffer, buffer_size);
    lfb_clear();
}

