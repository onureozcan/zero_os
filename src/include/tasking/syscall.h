//
// Created by onureozcan on 06.06.2019.
//

#ifndef ZEROOS_SYSCALL_H
#define ZEROOS_SYSCALL_H

#include <sys/stat.h>
#include <sys/times.h>

#define SYSCALL_EXIT 0
#define SYSCALL_CLOSE 1
#define SYSCALL_EXECVE 2
#define SYSCALL_FORK 3
#define SYSCALL_FSTAT 4
#define SYSCALL_GET_PID 5
#define SYSCALL_ISATTY 6
#define SYSCALL_KILL 7
#define SYSCALL_LINK 8
#define SYSCALL_LSEEK 9
#define SYSCALL_OPEN 10
#define SYSCALL_READ 11
#define SYSCALL_SBRK 12
#define SYSCALL_STAT 13
#define SYSCALL_TIMES 14
#define SYSCALL_UNLINK 15
#define SYSCALL_WAIT 16
#define SYSCALL_WRITE 17

void sys__exit(int code);

int sys_close(int file);

int sys_execve(char *name, char **argv, char **env);

int sys_fork();

int sys_fstat(int file, struct stat *st);

int sys_getpid();

int sys_isatty(int file);

int sys_kill(int pid, int sig);

int sys_link(char *old, char *new);

int sys_lseek(int file, int ptr, int dir);

int sys_open(const char *name, int flags, ...);

int sys_read(int file, char *ptr, int len);

void* sys_sbrk(int incr);

int sys_stat(const char *file, struct stat *st);

void* sys_times(struct tms *buf);

int sys_unlink(char *name);

int sys_wait(int *status);

int sys_write(int file, char *ptr, int len);

int syscall_dispatcher(int eax, int ebx, int ecx, int edx);

#endif //ZEROOS_SYSCALL_H
