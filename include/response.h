//
// Created by tunay on 4/23/25.
//

#ifndef RESPONSE_H
#define RESPONSE_H
#include <stddef.h>

typedef struct response {
    int status;
    char content_type[64];
    char *content;
    size_t content_length_size;
} server_response;


char *path = "../static/index.html";
char *path_error = "404";
int init_response(int clientfd, server_response *response);

#endif //RESPONSE_H
