//
// Created by tunay on 4/23/25.
//

#ifndef REQUEST_H
#define REQUEST_H


/**
 * @struct Request
 * @brief initialization request struct
 */
typedef struct {
    char *method; ///< method request
    char *path; ///< path to request
    char *version; ///< version request

}Request;

Request *request_init(int clientfd);

#endif //REQUEST_H
