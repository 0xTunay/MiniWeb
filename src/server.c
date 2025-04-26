//
// Created by tunay on 4/23/25.
//

#include "../include/server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void server_init() {
    struct sockaddr_in server_addres;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < -1) {
        perror("Error connection to the socket");
        exit(EXIT_FAILURE);
    }


    server_addres.sin_family = AF_INET;
    server_addres.sin_addr.s_addr = INADDR_ANY;
    server_addres.sin_port = htons(PORT);


}