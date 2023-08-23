#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (child_pid == 0) { // 자식 프로세스
        printf("This is the child process. PID: %d\n", getpid());
    } else { // 부모 프로세스
        printf("This is the parent process. PID: %d\n", getpid());
        printf("Child process PID: %d\n", child_pid);
    }

    // 부모와 자식 프로세스가 모두 실행되는 부분
    printf("This is executed by both parent and child. PID: %d\n", getpid());

    return 0;
}