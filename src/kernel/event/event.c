//
// Created by onureozcan on 12.07.2019.
//

#include <event/event.h>

static int subscriber_count = 0;
static event_handler_t listeners[EVENT_MAX_SUBSCRIBER_COUNT];

void event_publish(event_payload_t payload) {
    for (int i = 0; i < subscriber_count; i++) {
        listeners[i](payload);
    }
}

void event_subscribe(event_handler_t handler) {
    listeners[subscriber_count++] = handler;
}