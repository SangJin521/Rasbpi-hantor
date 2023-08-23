#ifndef __UTILLS_H__
#define __UTILLS_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void thread_creater(pthread_t *thd, void *(*func)(void *), void *arg);

void thread_joiner(pthread_t *thd_array, void **thd_status, int thd_size);

#endif