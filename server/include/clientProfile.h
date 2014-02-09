/*
 * File Name:		clientProfile.h
 * Author:			Emil Maric
 * Date Created:	Jan. 16, 2014	 
 *
 * Description:
 * Contains the prototypes for clientProfile.c
 */

#ifndef CLIENTPROFILE_H
#define CLIENTPROFILE_H

#include "shared_constants.h"
#include <netinet/in.h>
/*=============================================================================
 *	struct thread_info
 *-----------------------------------------------------------------------------
 * Description:
 * Each client connection on the server will consist of two threads; one for
 * reading messages sent by the client, and another for sending messages back
 * to this client which come from another user. The reason for this is so that
 * each client has a dedicated thread for receiving messages from the server.
 * If this method was not implemented, then the other option would be to 
 * iterate through a list of users. The issue with this is if while
 * broadcasting messages to all the clients, if there is a hangup with one
 * client, the clients following the stalled client will also see this delay.
 * Two dedicated threads for each client allow clients to not see the delay
 * posed by issues from other clients.
 *
 * This struct responsibility is to hold the thread id's responsible for 
 * receiving and sending messages to each client. In this sense, the two
 * threads form a client-pair.
 *
 * Parameters:
 * recv_tid		- receiving thread id
 * send_tid		- sending thread id
 *
 *=============================================================================
 */
struct thread_info {
	pthread_t		recv_tid;
	pthread_t		send_tid;
};


/*=============================================================================
 *	struct new_user
 *-----------------------------------------------------------------------------
 * Description:
 * Stores information about new connections.
 *
 * Parameters:
 * username		- The username the user has selected.
 * ip_adress	- The IP address of the user.
 * port			- The port from which the user is connected to.
 * sockfd		- The file-descriptor for the client on the server. 
 * thread_pair	- Points to the thread-pair for the client; receiving and 
 * 				  sending messages.
 * next			- Will point to the next user in a list.
 *
 *=============================================================================
 */
struct new_user {
	char					username[USERNAME_MAX_LENGTH];
	char					ip_address[INET6_ADDRSTRLEN];
	unsigned short			port;
	int						sockfd;
	struct thread_info 		*thread_pair;
	struct new_user			*next;
};


int create_user_profile(struct sockaddr_storage *sas, struct new_user *info);

#endif	// CLIENTPROFILE_H
