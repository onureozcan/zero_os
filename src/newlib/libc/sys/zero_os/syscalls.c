#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

extern void _exit(int code);

extern int close(int file);

char **environ = 0; /* pointer to array of char * strings that define the current environment variables */
extern int execve(char *name, char **argv, char **env);

extern int fork();

extern int fstat(int file, struct stat *st);

extern int getpid();

extern int isatty(int file);

extern int kill(int pid, int sig);

extern int link(char *old, char *new);

extern int lseek(int file, int ptr, int dir);

extern int open(const char *name, int flags, ...);

extern int read(int file, char *ptr, int len);

extern caddr_t sbrk(int incr);

extern int stat(const char *file, struct stat *st);

extern clock_t times(struct tms *buf);

extern int unlink(char *name);

extern int wait(int *status);

extern int write(int file, char *ptr, int len);
