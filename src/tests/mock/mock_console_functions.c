//
// Created by onureozcan on 01.06.2019.
//

//
// Created by onureozcan on 29.05.2019.
//

#include <stdarg.h>
#include <stdio.h>
#include <display/console.h>

void console_put_char(char c) {
   putchar(c);
}

void console_put_string(char *string) {
    int i = 0;
    char c = string[i];
    while (c != 0) {
        console_put_char(c);
        i++;
        c = string[i];
    }
}

void console_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE + 1] = {0};
    vsnprintf(buffer, KERNEL_CONSOLE_MAX_PRINTABLE_STRING_LENGTH_AT_ONCE, format, args);
    va_end(args);
    console_put_string(buffer);
}

void console_debug(const char *tag, const char *fmt, ...) {
}

void console_trace(const char *tag, const char *fmt, ...) {
}

void console_info(const char *tag, const char *fmt, ...) {
}

void console_warn(const char *tag, const char *fmt, ...) {
}


void console_error(const char *tag, const char *fmt, ...) {
}

void console_init() {

}

void panic(char* reason){
    console_put_string(reason);
    while (1);
}