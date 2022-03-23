#ifndef DEF_IPCTOOLS

#define DEF_IPCTOOLS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semalloc(key_t key, int valInit);
void P(int semid);
void V(int semid);
int semfree(int semid);

#endif
