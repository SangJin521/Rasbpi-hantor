#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void error_handler(char *message, int exit_flag) {
    fputs(message, stderr);
    fputc('\n', stderr);

    if (exit_flag == 1) {
        exit(1);
    }
}

void socket_sender(void *sender_args, int interval) {
    int serv_sock;
    socket_sender_info *connect_info = (socket_sender_info *)sender_args;

    printf("Waiting for Server connection to port %d...\n", connect_info->port);

    struct sockaddr_in serv_addr;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    if (serv_sock == -1) {
        error_handler("Server socket() error", true);
    }

    int opt = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(connect_info->port);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handler("Server bind() error", true);
    }

    if (listen(serv_sock, 5) == -1) {
        error_handler("Server listen() error", true);
    }       

    while (1) {
        int clnt_sock = -1;
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size;

        if (clnt_sock < 0)
        {
            clnt_addr_size = sizeof(clnt_addr);
            clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

            if (clnt_sock == -1) 
            {
                error_handler("Server accept() error", false);
                continue;
            }  
        }
        
        printf("Server connected! %d\n", connect_info->port);

        while (1) {
            if (connect_info->packet != 0) {
                char msg[2];

                strcpy(msg, connect_info->packet);
                msg[1] = '\0';

                if (write(clnt_sock, msg, strlen(msg) + 1) != -1) {
                    printf("Send message to Client: %s\n", msg);
                }
                else {
                    printf("Disconnected on port %d...\n", connect_info->port);
                    break;
                }
            }
            
            sleep(interval);
        }

        close(clnt_sock);
    }

    close(serv_sock);
}

void socket_receiver(void *receiver_args, int interval) {
    socket_receiver_info *connect_info = (socket_receiver_info *)receiver_args;

    while (1) {
        printf("Waiting for Client connection to %s:%d...\n", connect_info->address, connect_info->port);

        int sock;
        struct sockaddr_in serv_addr;
        char msg[2];

        sock = socket(PF_INET, SOCK_STREAM, 0);
        
        if (sock == -1) {
            error_handler("Client socket() error", false);
            sleep(interval);
            continue;
        }      
            
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(connect_info->address);
        serv_addr.sin_port = htons(connect_info->port);  
            
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) {
            error_handler("Client connect() error", false);
            sleep(interval);
            continue;
        }

        printf("Client connected! %s:%d\n", connect_info->address, connect_info->port);
                
        while(1) {                    
            if (read(sock, msg, sizeof(msg)) > 1) {
                printf("Receive message from Server : %s\n", msg);

                connect_info->packet = msg;
            }
            else {
                error_handler("Client read() error", false);
                break;
            }
        }

        close(sock);
    }
}

#endif