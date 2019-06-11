//
// Created by onureozcan on 02.06.2019.
//

#ifndef ZEROOS_PAGE_MANAGER_H
#define ZEROOS_PAGE_MANAGER_H

#include <stdint-gcc.h>
#include <multiboot.h>

#define PAGE_FLAGS_USER_ALSO 7
#define PAGE_FLAGS_KERNEL_ONLY 3
#define PAGES_PER_TABLE 1024
#define PAGES_PER_DIR    1024

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xfff)

typedef struct page_table {
    uint32_t pages[1024];
} page_table_t;

typedef struct page_directory {
    page_table_t *page_tables[1024];
} page_directory_t;

/**
 * will use multiboot info to get location and size of lfb.
 */
void page_manager_init(multiboot_info_t*);

/**
 * loads the identity page table for kernel only
 */
void page_manager_load_kernel_pages();

/**
 * creates an empty page directory.
 * @return
 */
page_directory_t *page_directory_new();

/**
 * creates a page table. aligns it 4K
 * @return
 */
page_table_t *page_table_new();

page_directory_t *page_manager_get_kernel_page_directory();

void page_manager_map_page(page_directory_t *page_directory, void *virtual_address, void *address, int is_kernel_only);

void page_manager_unmap_page(page_directory_t *page_directory, void *address);

/**
 * When kernel pages are loaded, old page directory is cached.
 * Once kernel done its work with pages, load old page table using this function
 */
void page_manager_restore_pages();

void *page_manager_virtual_to_physical(page_directory_t *page_directory, void *virtual_address);

extern void page_manager_load_page_directory(page_directory_t *page_directory);

#endif //ZEROOS_PAGE_MANAGER_H
