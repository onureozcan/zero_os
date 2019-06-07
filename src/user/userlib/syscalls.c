//
// Created by onureozcan on 07.06.2019.
//

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

static int make_syscall(int fnc, int arg0, int arg1, int arg2) {
    // TODO: how to do?
    return 0;
}

void _exit(int code) {
    make_syscall(0, code, 0, 0);
}

int close(int file) {
    return make_syscall(1, file, 0, 0);
}

int execve(char *name, char **argv, char **env) {
    return make_syscall(2, (int) (name), (int) argv, (int) env);
}

int fork() {
    return make_syscall(3, 0, 0, 0);
}

int fstat(int file, struct stat *st) {
    return make_syscall(4, file, (int) (st), 0);
}

int getpid() {
    return make_syscall(5, 0, 0, 0);
}

int isatty(int file) {
    return make_syscall(6, file, 0, 0);
}

int link(char *old, char *new) {
    return make_syscall(7, (int) (old), (int) new, 0);
}

int lseek(int file, int ptr, int dir) {
    return make_syscall(8, file, ptr, dir);
}

int open(const char *name, int flags, ...) {
    return make_syscall(9, (int) name, flags, 0);
}

int read(int file, char *ptr, int len) {
    return make_syscall(10, file, (int) ptr, len);
}

caddr_t sbrk(int incr) {
    return (void *) make_syscall(11, incr, 0, 0);
}

int stat(const char *file, struct stat *st) {
    return make_syscall(12, (int) file, (int) st, 0);
}

clock_t times(struct tms *buf) {
    return make_syscall(13, (int) buf, 0, 0);
}

int unlink(char *name) {
    return make_syscall(14, (int) name, 0, 0);
}

int wait(int *status) {
    return make_syscall(15, (int) status, 0, 0);
}

int write(int file, char *ptr, int len) {
    int buff[] = {(int) ptr, len};
    return make_syscall(16, (int) ptr, (int) buff, 0);
}