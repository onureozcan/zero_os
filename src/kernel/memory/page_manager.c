//
// Created by onureozcan on 02.06.2019.
//

#include <memory/page_manager.h>
#include <memory/memory_manager.h>
#include <common.h>
#include <display/console.h>
#include <tasking/task_manager.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "PAGE_MANAGER"

static void *lfb_start;
static uint32_t lfb_size;
static page_directory_t *kernel_pages;

page_table_t *get_ptable(page_directory_t *directory, uint32_t directory_index) {
    return (page_table_t *) (((uint32_t) directory->page_tables[directory_index]) & 0xFFFFF000);
}

void page_manager_map_lfb_pages(page_directory_t *page_directory) {
    uint32_t lfb_page_start = ((uint32_t) (lfb_start) / PAGE_SIZE_BYTES);
    uint32_t lfb_page_end = (((uint32_t) (lfb_start + lfb_size)) / PAGE_SIZE_BYTES) + 1;
    for (int i = lfb_page_start - 1; i < lfb_page_end; i++) {
        page_manager_map_page(page_directory, (void *) (i * PAGE_SIZE_BYTES), (void *) (i * PAGE_SIZE_BYTES), TRUE);
    }
}

void page_manager_init(multiboot_info_t *multiboot_info_ptr) {
    console_log(LOG_TAG, "init. identity mapping pages\n");
    kernel_pages = page_directory_new();
    for (int i = 0; i < memory_manager_get_total_number_of_pages(); i++) {
        page_manager_map_page(kernel_pages, (void *) (i * PAGE_SIZE_BYTES),
                              (void *) (i * PAGE_SIZE_BYTES), TRUE);
    }
    // get lfb address and size
    // will use this to map lfb pages
    lfb_start = (void *) multiboot_info_ptr->framebuffer_addr;
    lfb_size = (multiboot_info_ptr->framebuffer_width * multiboot_info_ptr->framebuffer_height *
                multiboot_info_ptr->framebuffer_bpp);
    page_manager_map_lfb_pages(kernel_pages);
}

void page_manager_load_kernel_pages() {
    page_manager_load_page_directory(kernel_pages);
    console_log(LOG_TAG, "loaded kernel pages at %p\n", kernel_pages);
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
    page_table_t *page_table = get_ptable(directory, directory_index);
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

void page_manager_restore_pages() {
    console_log(LOG_TAG, "restoring pages of latest process (%p)\n", current_process->page_directory);
    page_manager_load_page_directory(current_process->page_directory);
}

void *page_manager_virtual_to_physical(page_directory_t *page_directory, void *virtual_address) {
    uint32_t address_int = (uint32_t) virtual_address;
    uint32_t directory_index = PAGE_DIRECTORY_INDEX(address_int);
    uint32_t ptable_index = PAGE_TABLE_INDEX(address_int);
    uint32_t offset = address_int & 0xFFF;
    page_table_t *page_table = get_ptable(page_directory, directory_index);
    if (!page_table) {
        return NULL;
    }
    uint32_t mapped_base = page_table->pages[ptable_index];
    if (mapped_base == 0) {
        return NULL;
    } else {
        return (void *) ((mapped_base & 0xFFFFF000) + offset);
    }
}


page_directory_t *page_manager_get_kernel_page_directory() {
    return kernel_pages;
}
