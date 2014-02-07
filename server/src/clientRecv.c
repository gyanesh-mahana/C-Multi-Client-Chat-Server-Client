/*
 * File Name:	clientRecv.c
 * Author:		Emil Maric
 * Date:		Feb. 6, 2014	 
 *
 * Description:
 * Defines the client receiving thread on the server. In essense, this
 * thread exists on the server, and is responsible for handling messages
 * sent by the client, to the server. One of these threads is created for
 * each new client connected to the server.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "clientRecv.h"

/*=============================================================================
 *	client_receive_handler()
 *-----------------------------------------------------------------------------
 * Description:
 * Handles incomming messages from the client.
 *
 * Parameters:
 * *data	- holds network information about the client
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void *client_recv_handler(void *data) 
{
	//struct new_user		*client_info = (struct new_user *)data;

	//while(1) {
	//	if(recv(client_info->sockfd, ) < 0) {
	//	}
	//}

	pthread_exit(NULL);
}
