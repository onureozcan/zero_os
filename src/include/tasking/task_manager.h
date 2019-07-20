//
// Created by onureozcan on 04.06.2019.
//

#ifndef ZEROOS_TASK_MANAGER_H
#define ZEROOS_TASK_MANAGER_H

#include <memory/page_manager.h>
#include <stdint-gcc.h>
#include <common.h>
#include <display/console.h>
#include <fs/vfs.h>

#define PROCESS_STATE_SLEEP  0
#define PROCESS_STATE_ACTIVE 1

#define PROCESS_MAX_FILES_ALLOWED 128

#define MAIN_THREAD_DEFAULT_SP 0xFFFFFFFF
#define THREAD_INITIAL_STACK_FRAME_SIZE 4

typedef struct trap_frame {
    void *esp;
    void *ebp;
    void *eip;
    void *edi;
    void *esi;
    void *eax;
    void *ebx;
    void *ecx;
    void *edx;
    void *flags;
} trap_frame_t;

typedef struct thread {
    trap_frame_t trap_frame;
    struct thread *next;
    uint32_t tid;
    uint32_t pid;
    int state;
    void *user_stack;
    void *kernel_stack;
    uint32_t user_stack_size;
} thread_t;

typedef struct process {
    struct process *next;
    uint32_t pid;
    char *name;
    int state;
    int rr_count; // round robin count
    thread_t *current_thread;
    vfs_node_t *files[PROCESS_MAX_FILES_ALLOWED];
    page_directory_t *page_directory;
    void *v_program_break;
} process_t;

// linked list of all process
process_t *current_process;

// we use a pointer to the window manager to give control to it in case of mouse movement
process_t *window_manager;

thread_t *current_thread;

int tasking_enabled;

int tasking_initial;

/**
 * initializes and starts tasking.
 */
void task_manager_init();

/**
 * loads a task from bytes
 * @param name name of the task
 * @param bytes bytes of program (elf32)
 * @param args initial arguments
 * @param size size of args bytes
 * @return pid or NULL if failed
 */
uint32_t task_manager_load_process(char *name, char *bytes, char **args, uint32_t args_size);

/**
 * adds a new thread to an existing process
 * @param process process
 * @param eip initial eip of thread
 * @return thread id or NULL if failed
 */
uint32_t task_manager_add_thread(process_t *process, void *eip, void *stack);

process_t *task_manager_find_process_by_id(uint32_t pid);

/**
 * switches the next process with the given process.
 * @param process
 */
void task_manager_set_next_process(process_t* process);

void task_manager_next_task();

void *task_manager_sbrk(process_t *process, int size);

extern void task_manager_task_switch();

void task_manager_push_to_user_stack(process_t *process, thread_t *thread, uint32_t value);

/**
 * returns an index in the files list of process.
 * @param process process.
 * @return an index in the files array, -1 otherwise.
 */
int task_manager_get_file_handle(process_t *process);

#endif //ZEROOS_TASK_MANAGER_H
