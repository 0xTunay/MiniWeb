//
// Created by tunay on 4/23/25.
//

#include "../include/response.h"
#include "../include/request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

int  init_response(int clientfd, server_response *response, const char *path) {
    if (access(path,F_OK) == 0) {
        FILE *fp = fopen(path,"r");
        if (fp == NULL) {
            perror("fopen");
            fclose(fp);
            return 1;
        }

        const char accept_header[256];
        snprintf(accept_header,sizeof(accept_header),
                "HTTP/1.1 200 OK\r\nContent-Length: 14\r\nContent-Type: text/html\r\n\r\n");
        send(clientfd,accept_header,strlen(accept_header),0);
        send(clientfd,response->content, sizeof(response->content),0);
    } else {
        const char *not_found = "HTTP/1.1 404 Not Found\r\n"
                                "Content-Length: 13\r\n"
                                "Content-Type: text/plain\r\n"
                                "\r\n"
                                "404 Not Found";


        int so_sad = send(clientfd,not_found,strlen(not_found),0);
        if (so_sad == -1) {
            perror("send");
            return 1;
        }
    }
}