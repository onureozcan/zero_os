//
// Created by onureozcan on 30.05.2019.
//

#include <multiboot.h>
#include <display/console.h>
#include <memory/memory_manager.h>

void memory_manager_mmap_init(multiboot_memory_map_t *mmap_addr, uint32_t mmap_length) {
    uint64_t available_memory_in_bytes = 1; // 1 mb comes from lower memory
    multiboot_memory_map_t *mmap = mmap_addr;
    while (mmap < mmap_addr + mmap_length) {
        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            available_memory_in_bytes += mmap->len_low;
        }
        mmap = (multiboot_memory_map_t *) ((unsigned int) mmap + mmap->size + sizeof(mmap->size));
    }
    console_log(LOG_TAG, "initialized with %d mb memory\n", (available_memory_in_bytes / (1024 * 1024)));
}