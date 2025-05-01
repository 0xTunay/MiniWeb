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

    int total_bytes = 0;
    int buffer_size = 1024;

    char *request = NULL;
    request = (char*)malloc(buffer_size);
    if (!request) {
        return -1;

    }
    memset(request, 0, buffer_size);

    while (strtok(request, "\r\n\r\n") == NULL) {
        int received = recv(clientfd, request+ total_bytes, buffer_size - total_bytes, 0 );
        if (received == -1) {
            free(request);
            return -1;
        }
        if (received == 0) {
            close(clientfd);
            break;
        }

        total_bytes += received;
        request[total_bytes] = '\0';

        if (buffer_size - total_bytes < 128) {
            buffer_size *= 2;
            char *new_request = (char*) realloc(request, sizeof(char) * buffer_size);
            if (!new_request) {
                free(request);
                return -1;
            }
            request = new_request;
        }
    }

    printf("Request received: %s\n", request);

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

    free(request);
    return 0;
}
