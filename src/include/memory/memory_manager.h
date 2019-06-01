//
// Created by onureozcan on 30.05.2019.
//

#include <stdint-gcc.h>
#include <stddef.h>
#include <multiboot.h>

#ifndef ZEROOS_MEMORY_MANAGER_H

// 4 mb non paged area reserved for kernel use.
#define KERNEL_HEAP_SIZE_BYTES (1024*1024*4)

char kernel_heap_area[KERNEL_HEAP_SIZE_BYTES];


#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MEMORY_MANAGER"

/**
 * This function creates a data structure for 0(1) page frame allocation and deallocation.
 * Uses multiboot memory map.
 * @param mmap_addr multiboot memory map address
 * @param mmap_length multiboot memory map length
 */
void memory_manager_mmap_init(multiboot_memory_map_t *mmap_addr, uint32_t mmap_length);

/**
 * THis function initializes internal structures for k_malloc
 */
void memory_manager_malloc_init();

/* allocates a 4K aligned page frame. MUST be 0(1) */
void *memory_manager_alloc_page_frame();

/* de-allocates a 4K aligned page frame. MUST be 0(1) */
void memory_manager_free_page_frame(void *);

/**
 * There must be a non-paged area to use as a kernel heap space
 * This function allocates a chunk from this area.
 * literally a malloc replacement.
 */
void *k_malloc(size_t);

void *k_realloc(void *, size_t);

void k_free(void *);

#define ZEROOS_MEMORY_MANAGER_H

#endif //ZEROOS_MEMORY_MANAGER_H
