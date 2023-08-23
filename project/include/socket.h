#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef struct socket_sender_info_t{
   int port;
   char *packet;
} socket_sender_info;

typedef struct socket_receiver_info_t{
   int port;
   char *address;
   char *packet;
} socket_receiver_info;

void error_handler(char *message, int exit_flag);

void socket_sender(void *sender_args, int interval);

void socket_receiver(void *receiver_args, int interval);

#endif