//
// Created by tunay on 4/23/25.
//

#include "../include/server.h"
#include "../include/request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int sockfd = -1;

void handle_signal(int sig) {
    if (sockfd == -1) {
        printf("\n[+] Caught signal %d, shutting down...\n", sig);
        close(sockfd);
    }
    exit(0);
}
void server_init() {

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGHUP, handle_signal);

    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0) {
        perror("Error connection to the socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; /// ??
    server_addr.sin_port = htons(PORT);

    int optval = 1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) < 0) {
        perror("Error setting socket options");
        exit(EXIT_FAILURE);
    }
    if(bind(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
        perror("Binding error ");
        exit(EXIT_FAILURE);
    }
    if(listen(sockfd,2) == -1){
        perror("Error listen");
        exit(EXIT_FAILURE);
    }
    printf("Server start on port: %d\n",PORT);
    server_loop(sockfd);

}

void server_loop(int sockfd) {
    while (1) {
        int clientfd = accept(sockfd, ...);
        if (clientfd < 0) {
            perror("Error accepting connection");
            break;
        }
        printf("New client connected, fd: %d\n", clientfd);
        request_init(clientfd);
        close(clientfd);
    }
    close(sockfd);
	sockfd = -1;
}