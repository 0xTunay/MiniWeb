/*!
* @file server.c
 * @brief realization server for processing client connections
 * @author tunay
 * @date 2025-04-23
 */
#include "../include/server.h"
#include "../include/request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*!
 * @brief global desriptor socker server
 * @note inicialize -1, update in server_init()
 */
int sockfd = -1;


/*!
 *
 * @param sig number signal (for example SIGINT, SIGTERM, SIGHUG)
 */
void handle_signal(int sig) {
    if (sockfd >= 0) {
        printf("\n[+] Caught signal %d, shutting down...\n", sig);
        close(sockfd);
    }
    exit(0);
}

/*!
 * @brief initialization server
 * @details create socker configures its parametrs, connection to port and puts the socket into listening mode
        register signal handlers for SIGINT, SIGTERM, SIGHUP
    @note exit program with error if socket, configuration or listener is not created
 */
void server_init(void) {

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGHUP, handle_signal);

    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0) {
        perror("Error connection to the socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET; ///< IPv4 protocol
    server_addr.sin_addr.s_addr = INADDR_ANY; ///< accept connection any interface
    server_addr.sin_port = htons(PORT); ///< server port

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


/*!
 * @brief main server cycle for processing client connections
 * @param sockfd descriptor server socket
 * @details accept incoming connections from client initialization request through request_init()
 *          and close server socket after processting
 *
 *@note exit the loop if an error occurs with accept(), after which the server socket is closed
 *
 */

void server_loop(int sockfd) {
    while (1) {

	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
    int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &len);
	if(clientfd < 0) {
       perror("Error accepting connection");
		break;
	}
	char client_ip[INET_ADDRSTRLEN];
	inet_ntop (AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

        clientfd = accept(sockfd, NULL,NULL);
        if (clientfd < 0) {
            perror("Error accepting connection");
            break;
        }
        printf("New client connected, fd: %d\n", clientfd);
        request_init(clientfd);
        close(clientfd);
    }
    close(sockfd);
	sockfd = -1;
}