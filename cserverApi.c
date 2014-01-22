/*
 * File Name:	cserverApi.c
 * Author:	Emil Maric
 * Date:	January 16, 2014	 
 *
 * Description:
 * Contains the function implementations of the functions called in cserver.c.
 */

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <error.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include "cserverApi.h"
#include <sys/wait.h>
#include <signal.h>


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
	}
}


/*=============================================================================
 *	create_user_profile()
 *-----------------------------------------------------------------------------
 * Description:
 * Stores user's information into a 'new_user' struct
 *
 * Parameters:
 * *sa		- pointer to the structure holding the IP address 
 * *info	- holds the new user's information
 *
 * Return Value:
 * Returns 0 if everything is successful, otherwise -1
 *
 *=============================================================================
 */
int create_user_profile(struct sockaddr_storage *sas, struct new_user *info)
{
	char				new_ip4[INET_ADDRSTRLEN];	// Contains the IPv4 string
	char				new_ip6[INET6_ADDRSTRLEN];	// Contains the IPv6 string
	unsigned short		port_ip4, port_ip6;			// Holds the port number from the incoming connection
	unsigned long		addr_ip4;					// Holds the IPv4 struct value
	unsigned char		*addr_ip6;					// Holds the IPv6 struct value

	if (sas->ss_family == AF_INET) {	// Address is IPv4
		addr_ip4 = ((struct sockaddr_in *)sas)->sin_addr.s_addr;
		port_ip4 = ((struct sockaddr_in *)sas)->sin_port;
		port_ip4 = htons(port_ip4);			// Get the port of the connected user

		if(inet_ntop(AF_INET, &addr_ip4, new_ip4, sizeof(new_ip4)) == NULL) {
			perror("inet_ntop() [v4]");
			return -1;
		}
			
		strncpy(info->ip_address, new_ip4, sizeof(info->ip_address));		// Copy IP address to new_user struct
		info->port = port_ip4;												// Copy user's port to new_user struct
		printf("IP Address: \t%s\nPort: \t\t%i\nConnected to the server.\n\n\n\n", new_ip4, port_ip4);
		return 0;
	} 
	else if (sas->ss_family == AF_INET6) {		// Address is IPv6
		addr_ip6 = ((struct sockaddr_in6 *)sas)->sin6_addr.s6_addr;
		port_ip6 = ((struct sockaddr_in6 *)sas)->sin6_port;
		port_ip6 = htons(port_ip6);			// Get the port of the connected user

		if(inet_ntop(AF_INET6, &addr_ip6, new_ip6, sizeof(new_ip6)) == NULL) {
			perror("inet_ntop() [v6]");
			return -1;
		}
			
		strncpy(info->ip_address, new_ip6, sizeof(info->ip_address));		// Copy IP address to new_user struct
		info->port = port_ip6;												// Copy user's port to new_user struct
		printf("IP Address: \t%s\nPort: \t\t%i\nConnected to the server!\n\n\n\n", new_ip6, port_ip6);
		return 0;
	} 
	else {
		return -1;		// If it gets to here, then it is an error
	}	
}


/*=============================================================================
 *	client_receive_handler()
 *-----------------------------------------------------------------------------
 * Description:
 * Handles incomming messages from the client.
 *
 * Parameters:
 * *data	- holds information about the client
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void *client_recv_handler(void *data) 
{
	struct new_user		*client_info = (struct new_user *)data;

	//while(1) {
	//	if(recv(client_info->sockfd, ) < 0) {
	//	}
	//}

	pthread_exit(NULL);
}
