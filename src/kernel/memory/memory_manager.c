//
// Created by onureozcan on 30.05.2019.
//

#include <multiboot.h>
#include <display/console.h>
#include <memory/memory_manager.h>
#include <elf.h>

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

void memory_manager_set_kernel_used_areas(multiboot_elf_section_header_table_t elf_section_header) {
    Elf32_Shdr *section = elf_section_header.addr;
    uint32_t total_size = 0;
    for (int i = 0; i < elf_section_header.num; i++) {
        total_size += section->sh_size;
        console_log(LOG_TAG, "section %d: type: %d, address: %p. size: %d\n", i, section->sh_type, section->sh_addr,
                    section->sh_size);
        section++;
    }
    console_log(LOG_TAG, "total kernel reserved bytes:%d\n", total_size);
}