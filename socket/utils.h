#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>

void thread_creater(pthread_t *thd, void *(*func)(void *), void *arg) {
    int thr_id = pthread_create(thd, NULL, func, arg);

    if (thr_id < 0) {
        printf("Thread 생성 실패!\n");
        exit(0);
    }
}

void thread_joiner(pthread_t *thd_array, void **thd_status, int thd_size) {
    for (int i = 0; i < thd_size; i++) {
        pthread_join(thd_array[i], thd_status);
    }
}

#endif