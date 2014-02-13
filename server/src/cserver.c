/*
 * File Name:	cserver.c
 * Author:	Emil Maric
 * Date:	January 13, 2014	 
 *
 * Description:
 * Main function for Chat Server
 */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <pthread.h>
#include "server_recv_handler.h"
#include "kernPlus.h"
#include "shared_constants.h"
#include "server_constants.h"


int main(void)
{
    struct addrinfo				hints, *res, *i;
	struct sockaddr_storage		new_addr;
	struct new_user				*head = NULL;
	struct new_user				*user_info;
	struct thread_info			*thread_pair;
	socklen_t					new_addr_len;
	pthread_attr_t				attr;
    int							sockfd, newfd;
	int							yes	= 1;

	// Set-up hints struct for getaddrinfo()
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

	// Get local address info based on 'hints' struct
	get_address_info(NULL, CHATSERVER_PORT, &hints, &res);

    for(i = res; i != NULL; i = res->ai_next) {
		sockfd = socket(i->ai_family, i->ai_socktype, i->ai_protocol);	// Create a new unbound socket
		if (sockfd == -1) {
			perror("socket()");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) != 0) {	// Allow the socket to bind to a used IP/Port if it is in TIME_WAIT state
			close_socket(sockfd);
			perror("setsocketopt()");
			exit(EXIT_FAILURE);
		}

		if (bind(sockfd, i->ai_addr, i->ai_addrlen) != 0) {		// Bind socket to corresponding IP/Port
			close_socket(sockfd);
			perror("bind()");
			continue;
		}

		break;
    } 

	if (i == NULL) {
		fprintf(stderr, "No socket has been bound.\n\nExiting...\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(res);	// Free the addrinfo linked-list.

	if (listen(sockfd, BACKLOG) != 0) {		// Set the socket to 'listening' state
		close_socket(sockfd);
		perror("listen()");
		exit(1);
	}
	
	// Sets all new pthreads as detached ************************************** NEEDS ERROR CHECKING
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	printf("\nServer set-up complete!\nWaiting for new connections...\n\n\n");

	while(1) {	// Accept new connections at this point
		new_addr_len = sizeof(new_addr);
		newfd = accept(sockfd, (struct sockaddr *)&new_addr, &new_addr_len);	// Wait and accept new connection
		if (newfd == -1) {
			perror("accept()");
			continue;
		}

		printf("New connection!\nProcessing new connection...\n\n");

		// Filling in new_user struct
		user_info = (struct new_user *)malloc(sizeof(struct new_user));	// Allocate a new_user struct to store user information
		if (user_info == NULL) {
			fprintf(stderr, "Failed to allocate memory for a new_user struct\n");
			close_socket(newfd);
			exit(EXIT_FAILURE);
		}
		else {
			user_info->next = head;
			head = user_info;
		}

		if (create_user_profile(&new_addr, user_info) != 0) {		// Fill in a new_user struct with the user's information
			fprintf(stderr, "create_user_profile(): Incompatible Address Type\nConnection has been closed\n");
			close_socket(newfd);
			continue;
		}

		thread_pair = (struct thread_info *)malloc(sizeof(struct thread_info));		// Allocate a thread_info struct to hold the client's thread-pair
		if (thread_pair == NULL) {
			fprintf(stderr, "Failled to allocate memory for a thread_info struct");
			close_socket(newfd);
			exit(EXIT_FAILURE);
		}
		else {
			user_info->thread_pair = thread_pair;
			thread_pair = NULL;
		}

		user_info->sockfd = newfd;

		pthread_create(&(user_info->thread_pair->recv_tid), &attr, server_recv_handler, (void *)user_info);
		// pthread_create(&(user_info->thread_pair->send_tid), &attr, client_send_handler, (void *)user_info);	** FEATURE NOT AVAILABLE YET

		// Cleaning up
		user_info = NULL;
	}
}
