//
// Created by tunay on 4/23/25.
//

#ifndef REQUEST_H
#define REQUEST_H


typedef struct {
    char *method;
    char *path;
    char *version;

}Request;

Request *request_init(int clientfd);

#endif //REQUEST_H
