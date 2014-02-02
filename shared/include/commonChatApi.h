/*
 * File Name:	commonChatApi.h
 * Author:	Emil Maric
 * Date:	February 1, 2014	 
 *
 * Description:
 * Contains the function prototypes for commonChatApi.c.
 */

#ifndef COMMONCHATAPI_H
#define COMMONCHATAPI_H

void get_address_info(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);

void close_socket(int sockfd);

#endif	// COMMONCHATAPI_H

