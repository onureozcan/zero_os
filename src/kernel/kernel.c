//
// Created by onureozcan on 28.05.2019.
//
#include <display/console.h>
#include <cpu/gdt.h>
#include <multiboot.h>
#include <memory/memory_manager.h>
#include <elf.h>
#include <memory/page_manager.h>

// TODO: should it be here?
void panic(char *reason) {
    console_clear();
    console_put_string(reason);
    while (1);
}

void kmain(multiboot_info_t *multiboot_info_ptr, uint32_t magic) {
    console_init();
    console_put_string("initializing Zero Os ...\n");
    console_printf("multiboot info is located at %p. magic: %p\n", multiboot_info_ptr, magic);
    gdt_init();
    if (magic != 0x2BADB002) {
        console_printf("ERROR: multiboot magic bytes was corrupted.");
        return;
    }
    memory_manager_malloc_init();
    memory_manager_mmap_init((multiboot_memory_map_t *) multiboot_info_ptr->mmap_addr,
                             multiboot_info_ptr->mmap_length);
    memory_manager_set_kernel_used_areas(multiboot_info_ptr->u.elf_sec);
    page_manager_init();
}