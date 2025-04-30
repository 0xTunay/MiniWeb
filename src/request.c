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


int request_init(int clientfd){
    struct Request requests;

    char request[4096];

    int received = recv(clientfd, request, sizeof(request), 0);
    if(received == -1) {
        perror("recv");
        return -1;
    }
    printf("Request received: %s\n", request);
    request[received] = '\0';

    char *method = strtok(request, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, " ");

    if (!method || !path || !version) {
        perror("method/path/version not found");
        return -1;
    }

    requests.method = method;
    requests.path = path;
    requests.version = version;


    return 0;
}
