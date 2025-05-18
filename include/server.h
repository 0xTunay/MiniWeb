//
// Created by tunay on 4/23/25.
//

#ifndef SERVER_H
#define SERVER_H

/*!
 * @brief PORT default port server
 */
#define PORT 8080

/*!
 * @brief init server
 *
 */
void server_init(void);

/*!
 * @brief main server cycle for processing client connections
 *
 * */

void server_loop(int sock);

#endif //SERVER_H
