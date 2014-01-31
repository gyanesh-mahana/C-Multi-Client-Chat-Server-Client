/*
 * File Name:	cclientApi.c
 * Author:	Emil Maric
 * Date:	January 22, 2014	 
 *
 * Description:
 * Contains the function implementations of the functions called in cclient.c.
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/*=============================================================================
 *	send_all()
 *-----------------------------------------------------------------------------
 * Description:
 * Sends messages to server and checks to make sure that everything was sent.
 *
 * Parameters:
 *
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void send_all()



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
}
