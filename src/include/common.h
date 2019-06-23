//
// Created by onureozcan on 01.06.2019.
//

#ifndef ZEROOS_COMMON_H

#define TRUE 1
#define FALSE 0
#define NULL 0

#define LL_ERROR 1
#define LL_WARN 2
#define LL_INFO 3
#define LL_DEBUG 4
#define LL_TRACE 5

#define LOG_LEVEL LL_INFO

#define KERNEL_STACK_SIZE PAGE_SIZE_BYTES

#define ALIGN_4(size) (((size) + (4-1)) & ~(4-1))

#define ALIGN_4K(size) (((size) + (4096-1)) & ~(4096-1))

void panic(char* reason);

extern void write_port(uint32_t port,uint32_t data);
extern uint8_t read_port(uint32_t port);

#define ZEROOS_COMMON_H

#endif //ZEROOS_COMMON_H
