//
// Created by tunay on 4/23/25.
//
#include <stdio.h>
#include <stdlib.h>

#include "include/server.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(void) {
    int socket(AF_INET,SOCK_STREAM,0);
    puts("Mini web server with C lang");

    return 0;
}