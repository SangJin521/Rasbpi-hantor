#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../include/socket.h"
#include "../include/utils.h"
#include "../include/spi.h"

#define SENDER_PORT 10002

#define RECEIVER_PORT 10001
#define RECEIVER_ADDRESS "192.168.1.17"

#define INTERVAL 3

#define SPI_DEV_NUM 0


char send_packet[2] = "N";
char **recv_packet = NULL;

int *random_number = 0;

void *socket_sender_thd() {
    socket_sender_info *sender_args = (socket_sender_info *)malloc(sizeof(socket_sender_info));

    sender_args->port = SENDER_PORT;
    sender_args->packet = send_packet;
    
    socket_sender(sender_args, INTERVAL);

    return 0;
}

void *socket_receiver_thd(void *receiver_args) {
    socket_receiver_info *receiver_info = (socket_receiver_info *)receiver_args;

    receiver_info->address = RECEIVER_ADDRESS;
    receiver_info->port = RECEIVER_PORT;
    receiver_info->packet = NULL;
    
    recv_packet = &receiver_info->packet;

    socket_receiver(receiver_info, INTERVAL);

    return 0;
}

void *status_thd() {
    int fd = spi_init(SPI_DEV_NUM);

    if (fd == -1)
    {
        perror("spi_init");
        exit(0);
    }

    if (spi_set(fd) == -1)
    {
        perror("spi_set");
        exit(0);
    }

    while (1) {
        int water_level = read_adc(fd, 0);

        if (water_level > 0) {
            sprintf(send_packet, "y");
        } else {
            sprintf(send_packet, "n");
        }
                
        sleep(INTERVAL);
    }

    if (spi_final(fd) == -1)
    {
        perror("spi_final");
        exit(0);
    }

    return (0);
}

int main() {
    signal(SIGPIPE, SIG_IGN);

    pthread_t p_thread[3];

    socket_receiver_info *receiver_args = (socket_receiver_info *)malloc(sizeof(socket_receiver_info));

    int status;

    thread_creater(&p_thread[0], status_thd, NULL);
    thread_creater(&p_thread[1], socket_sender_thd, NULL);
    thread_creater(&p_thread[2], socket_receiver_thd, (void *)receiver_args);

    thread_joiner(p_thread, (void **)&status, sizeof(p_thread) / sizeof(pthread_t));

    return 0;
}