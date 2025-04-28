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
    struct sockaddr_in server_addr;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < -1) {
        perror("Error connection to the socket");
        exit(EXIT_FAILURE);
    }


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);


    if(bind(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
        perror("Binding error ");
        exit(EXIT_FAILURE);
    }

}