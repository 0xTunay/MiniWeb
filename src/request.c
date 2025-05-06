//
// Created by tunay on 4/23/25.
//

#include "../include/request.h"
#include "../include/response.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>



Request *request_init(int clientfd){

    Request *req = NULL;
    int total_bytes = 0;
    int buffer_size = 1024;
    char *request = NULL;
    char *header_end = NULL;

    req = malloc(sizeof(Request));
    if (!req) {
        perror("malloc");
        goto cleanup;
    }

    req->method = NULL;
    req->path = NULL;
    req->version = NULL;

    request = (char*)malloc(buffer_size);
    if (!request) {
        perror("malloc error");
        goto cleanup;
    }
    memset(request, 0, buffer_size);

    while (1) {
        int received = recv(clientfd, request+ total_bytes, buffer_size - total_bytes - 1, 0 ); // поговори со мноб бэби!
        if (received == -1) {
            perror("error receiving request");
            goto cleanup;
        }
        if (received == 0) {
            fprintf(stderr, "error receiving request\n");
            goto cleanup;
        }

        total_bytes += received;
        request[total_bytes] = '\0';

        header_end = strtok(request, "\r\n\r\n");
        if (header_end) {
            break;
        }
        if (buffer_size - total_bytes < 128) {
            buffer_size *= 2;
            if (buffer_size < 4098) {
                fprintf(stderr, "buffer_size is too small\n");
                goto cleanup;
            }
            char *new_request =  realloc(request, sizeof(char) * buffer_size);
            if (!new_request) {
                perror("realloc");
                goto cleanup;
            }
            request = new_request;
            memset(request + total_bytes, 0, buffer_size - total_bytes);
        }
    }
    char *line = NULL;
    line = strtok(request, "\r\n");
    if (!line) {
        fprintf(stderr, "invalid http request: no first line\n");
        goto cleanup;
    }
    printf("Request received: %s\n", request);

    char *method = strtok(request, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, " ");

    if (!method || !path || !version) {
        perror("method/path/version not found");
        goto cleanup;
    }

    /* copy to struct */

    req->method = strdup(method);
    if (!req->method) {
        perror("strdup error");
        goto cleanup;
    }

    req->path = strdup(path);
    if (!req->path) {
        perror("strdup error");
        goto cleanup;
    }
    req->version = strdup(version);
    if (!req->version) {
        perror("strdup error");
        goto cleanup;
    }


    server_response res;
    int result = init_response(clientfd,&res);
    if (result == -1) {
        fprintf(stderr, "init_response error\n");
        goto cleanup;
    }

    free(request);
    return req;
cleanup:
    free(request);
    free(req);
    free(req->method);
    free(req->path);
    free(req->version);
    return NULL;
}
