//
// Created by onureozcan on 28.05.2019.
//
#include <display/console.h>
#include <cpu/gdt.h>
#include <multiboot.h>
#include <memory/memory_manager.h>

void kmain(multiboot_info_t *multiboot_info_ptr, uint32_t magic) {
    console_init();
    console_put_string("initializing Zero Os ...\n");
    console_printf("multiboot info is located at %p. magic: %p\n", multiboot_info_ptr, magic);
    gdt_init();
    if (magic != 0x2BADB002) {
        console_printf("ERROR: multiboot magic bytes was corrupted.");
        return;
    }
    memory_manager_init((multiboot_memory_map_t *) multiboot_info_ptr->mmap_addr, multiboot_info_ptr->mmap_length);
}