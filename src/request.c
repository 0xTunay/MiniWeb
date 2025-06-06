//
// Created by tunay on 4/23/25.
//

/*!
 * @file request.c
 * @author Tunay
 * @date 2025-04-23
* @details Implement a user request initialization function that:
*    - Allocates memory for receiving data.
*    - Receives data from a socket.
*    - Copies the received data into a structure.
*    - Frees the allocated memory.
* @see request.h response.h
 */


#include "../include/request.h"
#include "../include/response.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>


/*!
 *
 * @param clientfd descriptor server socket
 */
Request *request_init(int clientfd){
    /*!
     * @details init default value
     */
    Request *req = NULL;
    int total_bytes = 0;
    int buffer_size = 1024;
    char *request = NULL;

    req = malloc(sizeof(Request));
    if (!req) {
        perror("malloc");
        goto cleanup;
    }

    req->method = NULL;
    req->path = NULL;
    req->version = NULL;

    request = (char*)malloc(buffer_size);
    if (!request) {
        perror("malloc error");
        goto cleanup;
    }
    memset(request, 0, buffer_size);
    /*!
     *
     * @details  read request through recv from the socket
     *      infinity cycle read data until we receive a complete HTTP request
     *
     */
    while (1) {
        int received = recv(clientfd, request+ total_bytes, buffer_size - total_bytes - 1, 0 ); // поговори со мноб бэби!
        if (received <= 0) {
			if(received == -1) perror("recv error");
			else fprintf(stderr, "recv error\n");
            goto cleanup;
        }
        /*!
         * @details if buffer size less 128, time to expand
         */
        total_bytes += received;
        request[total_bytes] = '\0';
		if(strstr(request, "\r\n\r\n")) break;
        if (buffer_size - total_bytes < 128) {
            buffer_size *= 2;
            if (buffer_size < 4098) {
                fprintf(stderr, "buffer_size is too small\n");
                goto cleanup;
            }
            char *new_request =  realloc(request,  buffer_size);
            if (!new_request) {
                perror("realloc");
                goto cleanup;
            }
            request = new_request;
            memset(request + total_bytes, 0, buffer_size - total_bytes);
        }
    }

    char *first_line_end = strstr(request, "\r\n");

    if(!first_line_end){
        fprintf(stderr, "error parsing request\n");
        goto cleanup;
    }

    /*!
     * @details take first line HTTP request and copy that separate for parse into mether,path,version
     */
    size_t first_line_len = first_line_end - request;
    char *first_line = strndup(request, first_line_len);
    if(!first_line){
        perror("strndup");
        goto cleanup;
    }
	char *method = strtok(first_line, " ");
	char *path = strtok(NULL, " ");
	char *version = strtok(NULL, " ");

    if (!method || !path || !version) {
        perror("method/path/version not found");
		free(first_line);
        goto cleanup;
    }

    /*!
     * @details copy to struct
     */

    req->method = strdup(method);
    if (!req->method) {
        perror("strdup error");
        goto cleanup;
    }

    req->path = strdup(path);
    if (!req->path) {
        perror("strdup error");
        goto cleanup;
    }
    req->version = strdup(version);
    if (!req->version) {
        perror("strdup error");
        goto cleanup;
    }


	server_response res = {0};
    if (init_response(clientfd, &res) < 0) {
        fprintf(stderr, "init_response error\n");
        free(res.content);
        goto cleanup;
    }
    /*
	printf("Attempting to log: %s %s %d\n", client_ip, req->path, res.status);
	FILE *log_file = fopen("./logs/log.txt", "a");
		if (log_file) {
  		  fprintf(log_file, "%s %s %d\n", client_ip, req->path, res.status);
   		 fclose(log_file);
		} else {
  			  perror("Failed to open log file");
	}
        */

    /*!
     * @details free all used memory
     */
    free(request);
	free(first_line);
    return req;
cleanup:
    free(request);
    if (req) {
        free(req->method);
        free(req->path);
        free(req->version);
        free(req);
    }
    return NULL;
}
