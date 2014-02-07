/*
 * File Name:	kernPlus.h
 * Author:		Emil Maric
 * Date:		February 1, 2014	 
 *
 * Description:
 * Contains the function prototypes for kernPlus.c.
 */

#ifndef KERNPLUS_H
#define KERNPLUS_H

void get_address_info(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);

void close_socket(int sockfd);

#endif	// KERNPLUS_H

