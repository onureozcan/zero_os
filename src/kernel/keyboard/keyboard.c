//
// Created by onureozcan on 12.07.2019.
//

#include <event/event.h>
#include <common.h>
#include <display/console.h>

static int caps_lock;
static int shift;
static int alt;
static int ctrl;

int is_shift(uint8_t scan_code) { return scan_code == 0x2A || scan_code == 0x36; }

int is_ctrl(uint8_t scan_code) { return scan_code == 0x1C || scan_code == 0x1D; }

int is_caps(uint8_t scan_code) { return scan_code == 0x3A; }

int is_alt(uint8_t scan_code) { return scan_code == 0x38 || scan_code == 0xE0; }

// this was at http://www.osdever.net/bkerndev/Docs/keyboard.htm
unsigned char keyboard_map[128] =
        {
                0, 27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
                '9', '0', '-', '=', '\b',    /* Backspace */
                '\t',            /* Tab */
                'q', 'w', 'e', 'r',    /* 19 */
                't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    /* Enter key */
                0,            /* 29   - Control */
                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',    /* 39 */
                '\'', '`', 0,        /* Left shift */
                '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
                'm', ',', '.', '/', 0,                /* Right shift */
                '*',
                0,    /* Alt */
                ' ',    /* Space bar */
                0,    /* Caps lock */
                0,    /* 59 - F1 key ... > */
                0, 0, 0, 0, 0, 0, 0, 0,
                0,    /* < ... F10 */
                0,    /* 69 - Num lock*/
                0,    /* Scroll Lock */
                0,    /* Home key */
                0,    /* Up Arrow */
                0,    /* Page Up */
                '-',
                0,    /* Left Arrow */
                0,
                0,    /* Right Arrow */
                '+',
                0,    /* 79 - End key*/
                0,    /* Down Arrow */
                0,    /* Page Down */
                0,    /* Insert Key */
                0,    /* Delete Key */
                0, 0, 0,
                0,    /* F11 Key */
                0,    /* F12 Key */
                0,    /* All other keys are undefined */
        };

static void keyboard_on_event(event_payload_t payload) {
    // this function is taken from http://www.osdever.net/bkerndev/Docs/keyboard.htm
    if (payload.code == EVENT_KEYBOARD_EVENT) {
        uint8_t scan_code = payload.data.uchar_val;
        /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
        if (scan_code & 0x80) {
            scan_code -= 0x80;
            /* You can use this one to see if the user released the
            *  shift, alt, or control keys... */
            if (is_shift(scan_code)) {
                shift = FALSE;
            }
            if (is_ctrl(scan_code)) {
                ctrl = FALSE;
            }
            if (is_alt(scan_code)) {
                alt = FALSE;
            }
        } else {
            /* Here, a key was just pressed. Please note that if you
            *  hold a key down, you will get repeated key press
            *  interrupts. */

            /* Just to show you how this works, we simply translate
            *  the keyboard scancode into an ASCII value, and then
            *  display it to the screen. You can get creative and
            *  use some flags to see if a shift is pressed and use a
            *  different layout, or you can add another 128 entries
            *  to the above layout to correspond to 'shift' being
            *  held. If shift is held using the larger lookup table,
            *  you would add 128 to the scancode when you look for it */

            char c = keyboard_map[scan_code];

            if (is_caps(scan_code)) {
                caps_lock = !caps_lock;
            } else if (is_shift(scan_code)) {
                shift = TRUE;
            } else if (is_ctrl(scan_code)) {
                ctrl = TRUE;
            } else if (is_alt(scan_code)) {
                alt = TRUE;
            }

            int is_enter = c == '\n';
            int is_lowercase = c > 97;

            if (alt && is_enter) {
                event_publish((event_payload_t) {
                        .code = EVENT_GUI_CONSOLE_SWITCH
                });
                return;
            }

            c = c + ((is_lowercase && (caps_lock || shift)) ? -32 : 0);
            console_put_char(c);
            console_repaint();
        }
    }
}

void keyboard_init() {
    event_subscribe((event_handler_t) keyboard_on_event);
}