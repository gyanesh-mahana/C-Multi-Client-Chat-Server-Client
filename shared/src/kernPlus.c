/*
 * File Name:	kernPlus.c
 * Author:		Emil Maric
 * Date:		January 22, 2014	 
 *
 * Description:
 * Contains common called kernel functions with additional error checking.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "kernPlus.h"


/*=============================================================================
 *	get_address_info()
 *-----------------------------------------------------------------------------
 * Description:
 * Executes the 'getaddrinfo()' function, and does additional error
 * checking to make sure the function returned properly.
 *
 * Parameters:
 * sockfd - a socket file descriptor
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void get_address_info(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
{
	int gai_result;

	gai_result = getaddrinfo(node, service, hints, res);
    if (gai_result != 0) {
		fprintf(stderr, "get_address_info() - %s\n", gai_strerror(gai_result));
		exit(EXIT_FAILURE);
    }

	return;
}


/*=============================================================================
 *	close_socket()
 *-----------------------------------------------------------------------------
 * Description:
 * Executes the 'close()' to close the socket, and does additional error
 * checking to make sure the socket was closed properly.
 *
 * Parameters:
 * sockfd - a socket file descriptor
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void close_socket(int sockfd)
{
	int close_result;

	close_result = close(sockfd);
	if (close_result == -1) {
		perror("close_socket()");
		exit(EXIT_FAILURE);
	}

	return;
}
