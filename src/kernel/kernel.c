//
// Created by onureozcan on 28.05.2019.
//
#include <display/console.h>
#include <cpu/gdt.h>
#include <multiboot.h>
#include <memory/memory_manager.h>
#include <elf.h>
#include <memory/page_manager.h>
#include <cpu/idt.h>
#include <cpu/tss.h>
#include <cpu/usermode.h>
#include <common.h>
#include <tasking/task_manager.h>
#include <tasking/init.h>
#include <display/lfb.h>
#include <fs/vfs.h>
#include <device/device.h>
#include <device/null/null.h>
#include <fs/volume/null/null.h>
#include <fs/root_fs/root_fs.h>
#include <fs/boot_fs/boot_fs.h>
#include <fs/dev_fs/dev_fs.h>
#include <device/framebuffer/framebuffer.h>
#include <keyboard/keyboard.h>
#include <event/event.h>
#include <device/mouse/mouse.h>

// TODO: should it be here?
void panic(char *reason) {
    console_put_string("PANIC:");
    console_put_string(reason);
    console_repaint();
    while (1);
}

char kernel_stack[KERNEL_STACK_SIZE] = {0};
int gui_available;

static void kernel_on_event(event_payload_t payload) {
    if (payload.code == EVENT_GUI_CONSOLE_SWITCH) {
        gui_available = !gui_available;
        if (gui_available) {
            lfb_disable();
            fb_device_enable();
        } else {
            fb_device_disable();
            lfb_enable();
            // to trigger a repaint
            console_printf(".\b");
        }
    }
}

void kmain(multiboot_info_t *multiboot_info_ptr, uint32_t magic) {

    // register event for gui - console switch
    event_subscribe((event_handler_t) kernel_on_event);

    memory_manager_malloc_init();
    lfb_init(multiboot_info_ptr->framebuffer_height, multiboot_info_ptr->framebuffer_width,
             (void *) ((uint32_t) multiboot_info_ptr->framebuffer_addr));

    // start in gui mode by default
    event_publish((event_payload_t) {
            .code = EVENT_GUI_CONSOLE_SWITCH
    });

    keyboard_init();
    console_init();
    console_put_string("initializing Zero Os ...\n");
    console_printf("multiboot info is located at %p. magic: %p\n", multiboot_info_ptr, magic);
    gdt_init();
    if (magic != 0x2BADB002) {
        panic("ERROR: multiboot magic bytes was corrupted.");
        return;
    }

    memory_manager_mmap_init((multiboot_info_ptr->mem_upper + multiboot_info_ptr->mem_lower) * 1024,
                             (multiboot_memory_map_t *) multiboot_info_ptr->mmap_addr,
                             multiboot_info_ptr->mmap_length);
    memory_manager_set_kernel_used_areas(multiboot_info_ptr->u.elf_sec);

    // device layer and vfs layer
    device_init();
    framebuffer_device_register(multiboot_info_ptr->framebuffer_height * multiboot_info_ptr->framebuffer_width *
                                LFB_DEPTH_BYTES,
                                (void *) ((uint32_t) multiboot_info_ptr->framebuffer_addr));
    null_device_register();
    null_volume_register();
    root_fs_init();
    boot_fs_init(multiboot_info_ptr);
    dev_fs_init();
    vfs_init();
    mouse_init();

    page_manager_init(multiboot_info_ptr);
    idt_init();

    // having the same stack in both user and kernel modes would cause gpf
    tss_init((uint32_t) &kernel_stack[KERNEL_STACK_SIZE - 1]);

    // load the hello program. if lucky, we will se a hello world in the screen printed by the user program
    init_load_hello();

    // load window manager
    init_load_window_manager(multiboot_info_ptr->framebuffer_height, multiboot_info_ptr->framebuffer_width,
                             multiboot_info_ptr->framebuffer_bpp);

    // enter user mode was just a test if we can go into the user mode or not.
    // since we proved that, no need to call it.
    // task manager is now on responsible for using user process if any.
    task_manager_init();

    //enter_user_mode();
}

void inside_user_mode() {
    console_printf("inside user mode!\n");
    while (1) {
    }
}