//
// Created by onureozcan on 06.06.2019.
//

#include <display/console.h>
#include <memory/page_manager.h>
#include <common.h>
#include <tasking/task_manager.h>
#include <tasking/syscall.h>
#include <memory/memory_manager.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "SYSCALL"


int syscall_dispatcher(int eax, int ebx, int ecx, int edx) {
    // we are dealing with user's data structures
    page_manager_load_kernel_pages();
    int ret = 0;
    console_log(LOG_TAG, "called fnc %d\n", eax);
    switch (eax) {
        case SYSCALL_EXIT:
            sys__exit(ebx);
            break;
        case SYSCALL_CLOSE:
            ret = sys_close(ebx);
            break;
        case SYSCALL_EXECVE:
            ret = sys_execve((char *) ebx, (char **) ecx, (char **) edx);
            break;
        case SYSCALL_FORK:
            ret = sys_fork();
            break;
        case SYSCALL_FSTAT:
            ret = sys_fstat(ebx, (struct stat *) ecx, edx);
            break;
        case SYSCALL_GET_PID:
            ret = sys_getpid();
            break;
        case SYSCALL_ISATTY:
            ret = sys_isatty(ebx);
            break;
        case SYSCALL_KILL:
            ret = sys_kill(ebx, ecx);
            break;
        case SYSCALL_LINK:
            ret = sys_link((char *) ebx, (char *) ecx);
            break;
        case SYSCALL_LSEEK:
            ret = sys_lseek(ebx, ecx, edx);
            break;
        case SYSCALL_OPEN:
            ret = sys_open((const char *) ebx, ecx, edx);
            break;
        case SYSCALL_READ:
            ret = sys_read(ebx, (char *) ecx, edx);
            break;
        case SYSCALL_SBRK:
            ret = (int) sys_sbrk(ebx);
            break;
        case SYSCALL_STAT:
            ret = sys_stat((const char *) ebx, (struct stat *) ecx);
            break;
        case SYSCALL_TIMES:
            ret = (int) sys_times((struct tms *) ebx);
            break;
        case SYSCALL_UNLINK:
            ret = sys_unlink((char *) ebx);
            break;
        case SYSCALL_WAIT:
            ret = sys_wait((int *) ebx);
            break;
        case SYSCALL_WRITE:
            ret = sys_write(ebx, (char *) ecx, edx);
            break;
    }
    page_manager_restore_pages();
    return ret;
}

void sys__exit(int code) {
    console_log(LOG_TAG, "exit %d\n", code);
};

int sys_close(int file) {
    console_log(LOG_TAG, "close %d\n", file);
    return 0;
};

int sys_execve(char *name, char **argv, char **env) {
    return 0;
};

int sys_fork() {
    return 0;
};

int sys_fstat(int file, struct stat *st, int size) {
    // we do not have a fs yet, so returning default values.
    void *physical = page_manager_virtual_to_physical(
            current_process->page_directory,
            (void *) st
    );
    if (!physical) { // TODO: in such cases, we will kill the process instead of killing the whole system
        panic("fstat has been fed an unmapped page");
    }
    struct stat *st_physical = physical;
    // FIXME: this causes page fault.
//    st_physical->st_dev = 0;
//    st_physical->st_ino = 0;
//    st_physical->st_mode = 777;
//    st_physical->st_nlink = 0;
//    st_physical->st_uid = 0;
//    st_physical->st_gid = 0;
//    st_physical->st_rdev = 0;
//    st_physical->st_dev = 0;
//    st_physical->st_size = KERNEL_CONSOLE_HEIGHT * KERNEL_CONSOLE_WIDTH;
//    st_physical->st_blksize = KERNEL_CONSOLE_WIDTH;
//    st_physical->st_blocks = 20;
//    st_physical->st_atime = 0;
//    st_physical->st_mtime = 0;
//    st_physical->st_ctime = 0;
    for (int i = 0; i < size; i++) {
        ((char *) (st_physical))[i] = 0;
    }
    console_log(LOG_TAG, "fstat: fd :%d, stat: %p physical, %p virtual\n", file, st_physical, st);
    console_log(LOG_TAG, "sizeof(stat), given sizeof(stat) : %d, %d\n", sizeof(struct stat), size);
    return 0;
};

int sys_getpid() {
    return 0;
};

int sys_isatty(int file) {
    return 0;
};

int sys_kill(int pid, int sig) {
    return 0;
};

int sys_link(char *old, char *new) {
    return 0;
};

int sys_lseek(int file, int ptr, int dir) {
    return 0;
};

int sys_open(const char *name, int flags, ...) {
    return 0;
};

int sys_read(int file, char *ptr, int len) {
    return 0;
};

void *sys_sbrk(int incr) {
    console_log(LOG_TAG, "sbrk gets called :%d bytes - %d pages\n", incr, incr / PAGE_SIZE_BYTES + 1);
    return task_manager_sbrk(current_process, incr);
}

int sys_stat(const char *file, struct stat *st) {
    return 0;
};

void *sys_times(struct tms *buf) {
    return 0;
}

int sys_unlink(char *name) {
    return 0;
};

int sys_wait(int *status) {
    return 0;
};

int sys_write(int file, char *ptr, int len) {
    char *physical = page_manager_virtual_to_physical(
            current_process->page_directory,
            (void *) ptr
    );
    if (!physical) { // TODO: in such cases, we will kill the process instead of killing the whole system
        panic("write has been fed an unmapped page");
    }
    console_log(LOG_TAG, "write called. fd:%d, virtual:%p, physical:%p , len:%p\n", file, ptr, physical, len);
    for (int i = 0; i < len; i++) {
        console_put_char(physical[i]);
    }
    console_repaint();
    return 0;
};