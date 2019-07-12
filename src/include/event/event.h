//
// Created by onureozcan on 12.07.2019.
//

#ifndef ZEROOS_EVENT_H
#define ZEROOS_EVENT_H

#include <stdint-gcc.h>

#define EVENT_MAX_SUBSCRIBER_COUNT 100

typedef struct event_payload {
    int code;
    union {
        int32_t int_val;
        int8_t char_val;
        int16_t short_val;
        int64_t long_val;
        uint32_t uint_val;
        uint8_t uchar_val;
        uint16_t ushort_val;
        uint64_t ulong_val;
    } data;
} event_payload_t;

typedef void (*event_handler_t)(event_payload_t);

void event_publish(event_payload_t);

void event_subscribe(event_handler_t);

#endif //ZEROOS_EVENT_H
