//
// Created by onureozcan on 30.05.2019.
//

#include <stdint-gcc.h>
#include <stddef.h>
#include <multiboot.h>

#ifndef ZEROOS_MEMORY_MANAGER_H

#define ZEROOS_MEMORY_MANAGER_H

// 4 mb non paged area reserved for kernel use.
#define KERNEL_HEAP_SIZE_BYTES (1024*1024*4)

char kernel_heap_area[KERNEL_HEAP_SIZE_BYTES];
uint32_t kernel_used_memory_in_bytes;

#define PAGE_SIZE_BYTES 4096
#define MAX_AMOUNT_OF_RAM_IN_BYTES (1024*1024*4096 -1)

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
void memory_manager_mmap_init(uint32_t,multiboot_memory_map_t *mmap_addr, uint32_t mmap_length);

/**
 * THis function initializes internal structures for k_malloc
 */
void memory_manager_malloc_init();

/**
 * This function takes elf section table and marks specific areas as as used by the kernel
 * so that these sections will never be given to a user program
 * */
void memory_manager_set_kernel_used_areas(multiboot_elf_section_header_table_t);

/* allocates a 4K aligned page frame */
void *memory_manager_alloc_page_frame();

/* de-allocates a 4K aligned page frame*/
void memory_manager_free_page_frame(void *);

int memory_manager_get_total_number_of_pages();

/**
 * There must be a non-paged area to use as a kernel heap space
 * This function allocates a chunk from this area.
 * literally a malloc replacement.
 */
void *k_malloc(size_t);

void *k_realloc(void *, size_t);

void k_free(void *);

#endif //ZEROOS_MEMORY_MANAGER_H
