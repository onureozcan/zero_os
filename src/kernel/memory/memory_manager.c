//
// Created by onureozcan on 30.05.2019.
//

#include <multiboot.h>
#include <display/console.h>
#include <memory/memory_manager.h>
#include <elf.h>
#include <common.h>

//! memory map bit array. Each bit represents a memory block
static uint32_t *memory_manager_memory_map = 0;
static int memory_manager_total_number_of_pages = 0;
static int memory_manager_number_of_free_pages = 0;

uint32_t mmap_is_used(uint32_t bit) {
    return memory_manager_memory_map[bit / 32] & (1 << (bit % 32));
}

void mmap_set(uint32_t bit) {
    if (!mmap_is_used(bit)) {
        memory_manager_number_of_free_pages--;
    }
    memory_manager_memory_map[bit / 32] |= (1 << (bit % 32));
}

static uint32_t memory_manager_get_page_number_from_address(uint32_t address) {
    return address / PAGE_SIZE_BYTES;
}

void mmap_unset(uint32_t bit) {
    if (mmap_is_used(bit)) {
        memory_manager_number_of_free_pages++;
    }
    memory_manager_memory_map[bit / 32] &= ~(1 << (bit % 32));
}

static void memory_manager_set_page_by_address(uint32_t address) {
    int index = memory_manager_get_page_number_from_address(address);
    mmap_set(index);
}

void *memory_manager_alloc_page_frame() {
    // The simplest solution.
    for (int i = 0; i < memory_manager_total_number_of_pages; i++) {
        if (!mmap_is_used(i)) {
            mmap_set(i);
            return (void *) (i * PAGE_SIZE_BYTES);
        }
    }
    return NULL;
}


static void memory_manager_unset_page_by_address(uint32_t address) {
    int index = memory_manager_get_page_number_from_address(address);
    mmap_unset(index);
}

void memory_manager_free_page_frame(void *ptr) {
    memory_manager_unset_page_by_address((uint32_t) ptr);
}

int memory_manager_get_total_number_of_pages() {
    return memory_manager_total_number_of_pages;
}

void memory_manager_mmap_init(multiboot_memory_map_t *mmap_addr, uint32_t mmap_length) {
    uint32_t available_memory_in_bytes = 0;
    uint32_t total_memory_in_bytes = 0;

    // in this iteration, detects total pages required
    multiboot_memory_map_t *mmap = mmap_addr;
    while (mmap < mmap_addr + mmap_length) {
        total_memory_in_bytes += mmap->len_low;
        mmap = (multiboot_memory_map_t *) ((unsigned int) mmap + mmap->size + sizeof(mmap->size));
    }
    if (total_memory_in_bytes > MAX_AMOUNT_OF_RAM_IN_BYTES) {
        // something is wrong. most probably mmap entries overlap.
        total_memory_in_bytes = MAX_AMOUNT_OF_RAM_IN_BYTES;
        console_log(LOG_TAG, "mmap reporting unrealistic total memory, probably it is overlapping");
    }


    // allocates  bitmap
    int required_pages = total_memory_in_bytes / PAGE_SIZE_BYTES;
    memory_manager_total_number_of_pages = required_pages;
    int required_bytes_for_mmap = required_pages / 8; // each byte is a block
    memory_manager_memory_map = k_malloc(required_bytes_for_mmap);

    // mark all the blocks as occupied initially. as we discover usable memory chunks we will clear them
    for (int i = 0; i < required_bytes_for_mmap / 4; i++) {
        memory_manager_memory_map[i] = 0xFFFFFFFF;
    }

    mmap = mmap_addr;
    // actually fills the page table bitmap
    while (mmap < mmap_addr + mmap_length) {
        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            available_memory_in_bytes += mmap->len_low;
            uint32_t unaligned_address = mmap->addr_low;
            uint32_t page_aligned_address = ALIGN_4K(unaligned_address);
            uint32_t length_diff = unaligned_address - page_aligned_address;
            uint32_t actual_length = mmap->len_low - length_diff;
            if (actual_length >= PAGE_SIZE_BYTES) {
                int number_of_pages_inside_this_block = actual_length / PAGE_SIZE_BYTES;
                uint32_t addr = page_aligned_address;
                for (int i = 0; i < number_of_pages_inside_this_block; i++) {
                    memory_manager_unset_page_by_address(addr);
                    addr += PAGE_SIZE_BYTES;
                }
            }
        }
        mmap = (multiboot_memory_map_t *) ((unsigned int) mmap + mmap->size + sizeof(mmap->size));
    }

    // reserves first 1 mb
    for (int i = 0; i < 256; i++) {
        mmap_set(i);
    }

    int available_mb = (available_memory_in_bytes / (1024 * 1024));
    int total_mb = (total_memory_in_bytes / (1024 * 1024));
    console_log(LOG_TAG, "initialized with %d mb usable and %d mb total memory\n", available_mb, total_mb);
}

void memory_manager_set_kernel_used_areas(multiboot_elf_section_header_table_t elf_section_header) {
    Elf32_Shdr *section = elf_section_header.addr;
    uint32_t total_size = 0;
    for (int i = 0; i < elf_section_header.num; i++) {
        total_size += section->sh_size;
//        console_log(LOG_TAG, "section %d: type: %d, address: %p. size: %d\n", i, section->sh_type, section->sh_addr,
//                    section->sh_size);
        int total_pages_needed_to_be_occupied = section->sh_size / PAGE_SIZE_BYTES + 1;
        uint32_t address = section->sh_addr;
        for (int j = 0; j < total_pages_needed_to_be_occupied; j++) {
            memory_manager_set_page_by_address(address);
            address += PAGE_SIZE_BYTES;
        }
        section++;
    }
    console_log(LOG_TAG, "kernel reserved:%d mb\n", total_size / (1024 * 1024));
    console_log(LOG_TAG, "%d mb available for user space out of %d mb\n",
                memory_manager_number_of_free_pages / 256,
                memory_manager_total_number_of_pages / 256);
}