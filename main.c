//
// Created by tunay on 4/23/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "include/server.h"

int main(void) {
    puts("Mini web server with C lang");
    server_init();
    return 0;
}