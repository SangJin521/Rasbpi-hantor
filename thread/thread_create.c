#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    int *thread_num = (int *)arg;
    printf("Thread %d is running.\n", *thread_num);
    // 스레드에서 수행할 작업 추가
    printf("Thread %d is done.\n", *thread_num);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int thread_arg = 1;  // 스레드 함수에 전달될 인수

    // 스레드 생성
    if (pthread_create(&thread, NULL, threadFunction, &thread_arg) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // 메인 스레드에서 수행할 작업 추가

    // 스레드가 종료될 때까지 기다림
    pthread_join(thread, NULL);

    printf("Thread has completed.\n");

    return 0;
}