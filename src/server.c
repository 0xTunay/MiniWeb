//
// Created by tunay on 4/23/25.
//

#include "../include/server.h"
#include "../include/request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/*TODO
 * эта хуйня не закрывает порт
 */
void server_init() {
    struct sockaddr_in server_addr;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0) {
        perror("Error connection to the socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    int optval = 1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) < 0) {
        perror("Error setting socket options");
        exit(EXIT_FAILURE);
    }
    if(bind(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
        perror("Binding error ");
        exit(EXIT_FAILURE);
    }
    if(listen(sockfd,2) == -1){
        perror("Error listen");
        exit(EXIT_FAILURE);
    }
    printf("Server start on port: %d\n",PORT);
    server_loop(sockfd);

}

void server_loop(int sockfd) {
	int clientfd;
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);

    while((clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &len)) >=0){

        request_init(clientfd);
        close(clientfd);
    }
    perror("Error accepting connection");

    close(clientfd);

}