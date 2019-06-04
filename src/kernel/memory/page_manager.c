//
// Created by onureozcan on 02.06.2019.
//

#include <memory/page_manager.h>
#include <memory/memory_manager.h>
#include <common.h>
#include <display/console.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "PAGE_MANAGER"

static page_directory_t *kernel_pages;

void page_manager_init() {
    console_log(LOG_TAG, "init. identity mapping pages\n");
    kernel_pages = page_directory_new();
    for (int i = 0; i < memory_manager_get_total_number_of_pages(); i++) {
        page_manager_map_page(kernel_pages, (void *) (i * PAGE_SIZE_BYTES),
                              (void *) (i * PAGE_SIZE_BYTES), TRUE);
    }
    page_manager_load_kernel_pages();
}

void page_manager_load_kernel_pages() {
    console_log(LOG_TAG, "loading kernel page directory located at %p\n", kernel_pages);
    page_manager_load_page_directory(kernel_pages);
}

void page_manager_map_page(page_directory_t *directory,
                           void *virtual_address, void *physical_address, int is_kernel_only) {
    uint32_t address_int = (uint32_t) virtual_address;
    uint32_t physical_address_int = (uint32_t) physical_address;
    uint32_t directory_index = PAGE_DIRECTORY_INDEX(address_int);
    uint32_t ptable_index = PAGE_TABLE_INDEX(address_int);
    physical_address_int &= 0xFFFFF000;
    if (is_kernel_only) {
        physical_address_int |= PAGE_FLAGS_KERNEL_ONLY;
    } else {
        physical_address_int |= PAGE_FLAGS_USER_ALSO;
    }
    page_table_t *page_table = (page_table_t *) (((uint32_t) directory->page_tables[directory_index]) & 0xFFFFF000);
    if (page_table == NULL) {
        page_table = page_table_new();
        uint32_t page_table_entry = (uint32_t) page_table;
        if (is_kernel_only) {
            page_table_entry |= PAGE_FLAGS_KERNEL_ONLY;
        } else {
            page_table_entry |= PAGE_FLAGS_USER_ALSO;
        }
        directory->page_tables[directory_index] = (page_table_t *) page_table_entry;
    }
    page_table->pages[ptable_index] = physical_address_int;
}

page_table_t *page_table_new() {
    page_table_t *page_table = memory_manager_alloc_page_frame();
    if (!page_table) {
        panic("out of memory");
    }
    for (int i = 0; i < PAGES_PER_TABLE; i++) {
        page_table->pages[i] = 0;
    }
    return page_table;
}

page_directory_t *page_directory_new() {
    page_directory_t *page_directory = memory_manager_alloc_page_frame();
    if (!page_directory) {
        panic("out of memory");
    }
    for (int i = 0; i < PAGES_PER_DIR; i++) {
        page_directory->page_tables[i] = NULL;
    }
    return page_directory;
}
