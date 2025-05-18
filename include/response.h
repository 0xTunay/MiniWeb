//
// Created by tunay on 4/23/25.
//

#ifndef RESPONSE_H
#define RESPONSE_H
#include <stddef.h>

/*!
 * @struct server_response
 * @details struct processing response server
 */
typedef struct {
    int status;  ///< status server (404, 200 and etc)
    char content_type[64]; ///< context type (png,curl,html)
    char *content; ///< buffer size
    size_t content_length; ///< length response
} server_response;

/*!
 *
 * @param clientfd desriptor server socker
 * @param response response server
 * @return
 */
int init_response(int clientfd, server_response *response);

#endif //RESPONSE_H
