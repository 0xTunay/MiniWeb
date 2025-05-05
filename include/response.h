//
// Created by tunay on 4/23/25.
//

#ifndef RESPONSE_H
#define RESPONSE_H
#include <stddef.h>

typedef struct {
    int status;
    char content_type[64];
    char *content;
    size_t content_length;
} server_response;


int init_response(int clientfd, server_response *response);

#endif //RESPONSE_H
