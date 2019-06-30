//
// Created by onureozcan on 04.06.2019.
//

#include <tasking/task_manager.h>
#include <elf/elf.h>
#include <display/console.h>
#include <stddef.h>
#include <memory/memory_manager.h>
#include <cpu/idt.h>
#include <common.h>
#include <string/k_string.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TASK_MANAGER"

void task_manager_init() {
    clear_interrupts();
    tasking_enabled = TRUE;
    tasking_initial = TRUE;
    task_manager_task_switch();
}

uint32_t task_manager_load_process(char *name, char *bytes, char **args, uint32_t args_size) {

    Elf32_Ehdr *elf_header = (Elf32_Ehdr *) bytes;
    console_info(LOG_TAG, "load process %s\n", name);

    // validate elf file
    char *ident = (char *) elf_header->e_ident;
    if (ident[0] == ELFMAG0
        && ident[1] == ELFMAG1
        && ident[2] == ELFMAG2
        && ident[3] == ELFMAG3) {
        int type = elf_header->e_type;
        int machine = elf_header->e_machine;
        int os_abi = elf_header->e_ident[EI_OSABI];
        if (type == ET_EXEC) {
            if (machine == EM_386) {
                if (os_abi == ELFOSABI_NONE) {
                    goto elf_file_valid;
                } else {
                    console_debug(LOG_TAG, "elf os abi was not 0\n");
                    goto error_return;
                }
            } else {
                console_debug(LOG_TAG, "elf machine was not i386\n");
                goto error_return;
            }
        } else {
            console_debug(LOG_TAG, "elf type was not executable\n");
            goto error_return;
        }
    } else {
        console_debug(LOG_TAG, "elf ident was broken\n");
        goto error_return;
    }

    elf_file_valid:
    {
        // clear interrupts to prevent task switch during initialization
        clear_interrupts();

        // since we are dealing with page related things, we need to full access to the memory
        page_manager_load_kernel_pages();

        process_t *process = (process_t *) k_malloc(sizeof(process_t));
        process->name = name;
        process->pid = (uint32_t) process; // this is silly
        process->state = PROCESS_STATE_ACTIVE;
        process->page_directory = page_directory_new();
        process->current_thread = NULL;
        for (int i = 0; i < PROCESS_MAX_FILES_ALLOWED; i++) {
            process->files[i] = NULL;
        }
        // map kernel pages to newly initialized directory
        // 256 for 0-1MB
        int kernel_page_count = kernel_used_memory_in_bytes / PAGE_SIZE_BYTES + 1 + 256;
        for (int i = 0; i < kernel_page_count; i++) {
            page_manager_map_page(process->page_directory, (void *) (i * PAGE_SIZE_BYTES),
                                  (void *) (i * PAGE_SIZE_BYTES), TRUE);
        }

        if (current_process) {
            process->next = current_process->next;
            current_process->next = process;
        } else {
            current_process = process;
            process->next = process;
        }

        console_debug(LOG_TAG, "program image is valid, loading sections..\n");

        Elf32_Shdr *section = (Elf32_Shdr *) (bytes + elf_header->e_shoff);
        uint32_t section_count = elf_header->e_shnum;

        for (int i = 0; i < section_count; i++) {
            if (section->sh_addr) {

                process->v_program_break = (void *) (section->sh_addr + section->sh_size);
                console_debug(LOG_TAG, "section %d: type: %d, address: %p. size: %d\n", i, section->sh_type,
                              section->sh_addr,
                              section->sh_size);

                uint32_t current_virtual_addr = section->sh_addr;
                uint32_t total_bytes_to_load = section->sh_size;
                uint32_t total_bytes_loaded = 0;

                while (total_bytes_loaded < section->sh_size) {

                    void *source = bytes + section->sh_offset + total_bytes_loaded;
                    uint32_t virtual_page_number_lower = current_virtual_addr / PAGE_SIZE_BYTES;
                    uint32_t virtual_page_number_upper = virtual_page_number_lower + 1;

                    uint32_t virtual_page_boundary_upper = virtual_page_number_upper * PAGE_SIZE_BYTES;
                    uint32_t virtual_page_boundary_lower = virtual_page_number_lower * PAGE_SIZE_BYTES;

                    uint32_t bytes_to_load_for_page = virtual_page_boundary_upper - current_virtual_addr;

                    if (total_bytes_to_load < bytes_to_load_for_page) {
                        bytes_to_load_for_page = total_bytes_to_load;
                    }

                    void *physical = page_manager_virtual_to_physical(process->page_directory,
                                                                      (void *) (current_virtual_addr));
                    if (!physical) {
                        // not mapped
                        void *new_frame = memory_manager_alloc_page_frame();
                        page_manager_map_page(process->page_directory,
                                              (void *) virtual_page_boundary_lower, new_frame,
                                              FALSE);
                        physical = page_manager_virtual_to_physical(process->page_directory,
                                                                    (void *) (current_virtual_addr));
                    }
                    console_debug(LOG_TAG, "%d bytes from %p, loaded to physical %p virtual %p\n",
                                  bytes_to_load_for_page,
                                  source, physical,
                                  current_virtual_addr);

                    if (section->sh_type == SHT_NOBITS) {
                        for (int j = 0; j < bytes_to_load_for_page; j++) {
                            ((char *) physical)[j] = 0;
                        }
                    } else {
                        memcpy(physical, source, bytes_to_load_for_page);
                    }
                    current_virtual_addr += bytes_to_load_for_page;
                    total_bytes_loaded += bytes_to_load_for_page;
                    total_bytes_to_load -= bytes_to_load_for_page;
                }
            }
            section++;
        }


        console_debug(LOG_TAG, "loaded to the memory, adding main thread\n");
        task_manager_add_thread(process, (void *) elf_header->e_entry, (void *) MAIN_THREAD_DEFAULT_SP);

        for (int i = 0; i < args_size; i++) {
            task_manager_push_to_user_stack(process, process->current_thread, (uint32_t) args[i]);
        }
        task_manager_push_to_user_stack(process, process->current_thread,
                                        (uint32_t) (MAIN_THREAD_DEFAULT_SP - 4)); // argsv
        task_manager_push_to_user_stack(process, process->current_thread, (uint32_t) args_size); // argsc

        store_interrupts();
        console_debug(LOG_TAG, "loaded %p\n", process->pid);
        return process->pid;
    }
    error_return:
    panic("could not load process\n");
    return 0;
}

void task_manager_push_to_user_stack(process_t *process, thread_t *thread, uint32_t value) {

    thread->trap_frame.esp -= 4;
    get_physical_addr:;
    uint32_t *user_stack_physical = (uint32_t *) page_manager_virtual_to_physical(process->page_directory,
                                                                                  (void *) thread->trap_frame.esp);
    if (!user_stack_physical) {
        // if not mapped, first alloc a page and map it
        int page_number = (uint32_t) thread->trap_frame.esp / PAGE_SIZE_BYTES;
        void *page_aligned_virtual_address = (void *) (page_number * PAGE_SIZE_BYTES);
        page_manager_map_page(process->page_directory, page_aligned_virtual_address, memory_manager_alloc_page_frame(),
                              FALSE);
        console_debug(LOG_TAG, "adding stack frame to thread %p, %p\n", thread, thread->trap_frame.esp);
        goto get_physical_addr;
    }
    // already mapped, then simply put
    *user_stack_physical = value;

}

uint32_t task_manager_add_thread(process_t *process, void *eip, void *stack) {

    console_debug(LOG_TAG, "adding new thread to %d with eip %p\n", process->pid, eip);
    thread_t *thread = (thread_t *) k_malloc(sizeof(thread_t));
    thread->state = PROCESS_STATE_ACTIVE;
    thread->pid = process->pid;
    thread->tid = (uint32_t) thread;
    thread->trap_frame.eip = eip;
    thread->trap_frame.esp = stack;
    thread->next = NULL;
    thread->user_stack_size = PAGE_SIZE_BYTES * THREAD_INITIAL_STACK_FRAME_SIZE;
    for (int i = 0; i < THREAD_INITIAL_STACK_FRAME_SIZE; i++) {
        console_trace(LOG_TAG, "mapping stack frame %p\n", stack - PAGE_SIZE_BYTES * i);
        page_manager_map_page(process->page_directory,
                              stack - PAGE_SIZE_BYTES * i,
                              memory_manager_alloc_page_frame(),
                              FALSE);
    }
    // if not the first thread
    if (process->current_thread) {
        thread->next = process->current_thread->next;
        process->current_thread->next = thread;
    } else {
        process->current_thread = thread;
        // cyclic
        thread->next = thread;
    }
    return thread->tid;

}

void task_manager_next_task() {
    current_thread = current_process->current_thread->next;
    page_manager_load_page_directory(current_process->page_directory);
}

void *task_manager_sbrk(process_t *process, uint32_t inc) {

    void *old_break = process->v_program_break;
    uint32_t current_virtual_addr = (uint32_t) process->v_program_break;
    uint32_t total_bytes_to_load = inc;
    uint32_t total_bytes_loaded = 0;

    while (total_bytes_loaded < total_bytes_to_load) {

        uint32_t virtual_page_number_lower = current_virtual_addr / PAGE_SIZE_BYTES;
        uint32_t virtual_page_number_upper = virtual_page_number_lower + 1;

        uint32_t virtual_page_boundary_upper = virtual_page_number_upper * PAGE_SIZE_BYTES;
        uint32_t virtual_page_boundary_lower = virtual_page_number_lower * PAGE_SIZE_BYTES;

        uint32_t bytes_to_load_for_page = virtual_page_boundary_upper - current_virtual_addr;

        if (total_bytes_to_load < bytes_to_load_for_page) {
            bytes_to_load_for_page = total_bytes_to_load;
        }

        void *physical = page_manager_virtual_to_physical(process->page_directory,
                                                          (void *) (current_virtual_addr));
        if (!physical) {
            // not mapped
            void *new_frame = memory_manager_alloc_page_frame();
            page_manager_map_page(process->page_directory,
                                  (void *) virtual_page_boundary_lower, new_frame,
                                  FALSE);
        }
        current_virtual_addr += bytes_to_load_for_page;
        total_bytes_loaded += bytes_to_load_for_page;
        total_bytes_to_load -= bytes_to_load_for_page;
        process->v_program_break += bytes_to_load_for_page;
    }
    console_debug(LOG_TAG, "%d bytes added process %p. new brk is %p\n",
                  total_bytes_loaded,
                  process->pid,
                  process->v_program_break);
    return old_break;
}

int task_manager_get_file_handle(process_t *process) {
    // starts from 3 because first 3 are std io
    for (int i = 3; i < PROCESS_MAX_FILES_ALLOWED; i++) {
        if (process->files[i] == NULL) {
            return i;
        }
    }
    return -1;
}