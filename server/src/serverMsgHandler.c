/*
 * File Name:	serverMsgHandler.c
 * Author:		Emil Maric
 * Date:		Feb. 6, 2014	 
 *
 * Description:
 * Defines the threads the server assigns to each connected client to handle
 * messages sent from and to the client.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "serverMsgHandler.h"

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
void *server_recv_handler(void *data) 
{
	//struct new_user		*client_info = (struct new_user *)data;

	//while(1) {
	//	if(recv(client_info->sockfd, ) < 0) {
	//	}
	//}

	pthread_exit(NULL);
}
