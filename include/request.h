//
// Created by tunay on 4/23/25.
//

#ifndef REQUEST_H
#define REQUEST_H

int request_init();


struct Request {
    char *method;
    char *path;
    char *version;

};

#endif //REQUEST_H
