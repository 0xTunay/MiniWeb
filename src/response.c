//
// Created by tunay on 4/23/25.
//

#include "../include/response.h"
#include "../include/mime.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/socket.h>

int  init_response(int clientfd, server_response *response) {

    const char *path = "./static/index.html";

    if (access(path,F_OK) == 0) {
        FILE *fp = fopen(path,"r");
        if (fp == NULL) {
            perror("fopen");
            return 1;
        }
        fseek(fp,0,SEEK_END);
        long size_file = ftell(fp);

        if (size_file == -1) {
            perror("ftell");
            fclose(fp);
            return -1;
        } // super technology
        if (size_file >= LONG_MAX) {
            fprintf(stderr, "File size too large\n");
            fclose(fp);
            return -1;
        }
        fseek(fp,0,SEEK_SET);
        char *buffer = malloc(size_file);
        if (buffer == NULL) {
            perror("malloc");
            return -1;
        }
        size_t bytes_read = fread(buffer, 1, size_file, fp);
        if (bytes_read != size_file) {
            fprintf(stderr, "Read %zu bytes, expected %ld\n", bytes_read, size_file);
            free(buffer);
            fclose(fp);
            return -1;
        }
        response->content_length = bytes_read;

        const char *extention = strrchr(path, '.');
        if (extention) {
            extention++;
        }else {
            extention = "txt";
        }
        const char *mime_type = get_type(extention);

        char accept_header[256];
        snprintf(accept_header, sizeof(accept_header),
                "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: %s\r\n\r\n",
                response->content_length, mime_type);
        printf("sending header %s", accept_header);
        size_t total_send = 0;
        size_t header_len = strlen(accept_header);
        while(total_send < header_len){

            int sent = send(clientfd, accept_header + total_send, header_len - total_send, 0);
            if(send == -1){
                perror("send header");
                return -1;


            }
            total_send += send;
        }
        printf("Sending %zu bytes of content: %.*s\n", response->content_length, (int)response->content_length, response->content);
        total_send = 0;
        while (total_send < response->content_length) {
            int sent = send(clientfd, response->content + total_send, response->content_length - total_send, 0);
            if (sent == -1) {
                perror("send content");
                return -1;
            }
            total_send += sent;
        }            int so_fine = send(clientfd, accept_header, strlen(accept_header), 0);
        if (so_fine == -1) {
            perror("send");
            return -1;
        }



        int so_good = send(clientfd, response->content, response->content_length, 0);
        if (so_good == -1) {
            perror("send");
            return -1;
        }

        response->status = 200;
        response->content_length = size_file;
        strcpy(response->content_type,mime_type);
        strcpy(response->content_type,"text/html");

    } else {
        const char *not_found = "HTTP/1.1 404 Not Found\r\n"
            "Content-Length: 13\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "404 Not Found";

        response->status = 404;
        strcpy(response->content_type, "text/plain");
        response->content = "404 Not Found";
        response->content_length = 13;

        int so_sad = send(clientfd,not_found,strlen(not_found),0);
        if (so_sad == -1) {
            perror("send");
            return 1;
        }
    }

    return 0;
}
