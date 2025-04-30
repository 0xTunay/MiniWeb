//
// Created by tunay on 4/23/25.
//

#include "../include/request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int request_init(){
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(80);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return -1;
    }

    socklen_t len = sizeof(server);
    bind(sock, (struct sockaddr *) &server, len));

    if (connect(sock, (struct sockaddr *)&server, len) == -1) {
        perror("connect");
        return -1;
    }
    return sock;

}
