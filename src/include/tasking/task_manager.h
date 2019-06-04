//
// Created by onureozcan on 04.06.2019.
//

#ifndef ZEROOS_TASK_MANAGER_H
#define ZEROOS_TASK_MANAGER_H

#include <memory/page_manager.h>
#include <stdint-gcc.h>

#define PROCESS_STATE_SLEEP  0
#define PROCESS_STATE_ACTIVE 1

typedef struct trap_frame {
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t edi;
    uint32_t esi;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t flags;
} trap_frame_t;

typedef struct thread {
    struct thread *next;
    uint32_t tid;
    uint32_t pid;
    int state;
    void *user_stack;
    void *kernel_stack;
    trap_frame_t trap_frame;
} thread_t;

typedef struct process {
    struct process *next;
    uint32_t pid;
    char *name;
    int state;
    thread_t *current_thread;
    struct { // these will have meaning once vfs is implemented
        uint32_t stdin;
        uint32_t stderr;
        uint32_t stdout;
    };
    page_directory_t* page_directory;
} process_t;

// linked list of all process
process_t *current_process;

/**
 * initializes and starts tasking.
 */
void task_manager_init();

/**
 * loads a task from bytes
 * @param name name of the task
 * @param bytes bytes of program (elf32)
 * @param size size of bytes
 * @return pid or NULL if failed
 */
uint32_t task_manager_load_process(char *name, char *bytes, uint32_t size);

/**
 * adds a new thread to an existing process
 * @param process process
 * @param eip initial eip of thread
 * @return thread id or NULL if failed
 */
uint32_t task_manager_add_thread(process_t* process, uint32_t eip);

#endif //ZEROOS_TASK_MANAGER_H
