/*
 * File Name:	cclient.c
 * Author:	Emil Maric
 * Date:	January 21, 2014	 
 *
 * Description:
 * Client Code for the chat server
 */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

#include "clientMsgHandler.h"

#define NUM_THREADS 2

#include "kernPlus.h"
#include "shared_constants.h"


int main(int argc, char *argv[])
{
	struct addrinfo		hints, *res, *i;
	int					sockfd, gai_result;
	char				*server_ip;

    //Variables for threads
      pthread_t threads[NUM_THREADS];
      long t = 5;

	if (argc != 2) {
		fprintf(stderr, "usage: cclient serverip\nserverip - ip address of the chat server\n");
		exit(EXIT_FAILURE);
	}
	else {
		server_ip = argv[1];
	}

	// Set-up hints struct for getaddrinfo()
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

	// Get address info based on 'hints' struct
    gai_result = getaddrinfo(server_ip, CHATSERVER_PORT, &hints, &res);
    if (gai_result != 0) {
		fprintf(stderr, "getaddrinfo() - %s\n", gai_strerror(gai_result));
		exit(EXIT_FAILURE);
    }
	
	// Attempt to connect socket to chat server
    for(i = res; i != NULL; i = res->ai_next) {
		sockfd = socket(i->ai_family, i->ai_socktype, i->ai_protocol);	// Create a new unbound socket
		if (sockfd == -1) {
			perror("socket()");
			continue;
		}

		// Attempt to connect to chat server
		if (connect(sockfd, i->ai_addr, i->ai_addrlen) != 0) {
			perror("connect()");
			close_socket(sockfd);
			continue;
		}	
		
		break;
    } 

	// If 'i' gets to the end of the list, then no connection was made.
	if (i == NULL) {
		fprintf(stderr, "No connection could be made to the server.\n\nExiting...\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(res);	// Free the addrinfo linked-list

	printf("Connected to the chat server!\n");

	if(( pthread_create(&threads[0], NULL, SendMessage, (void*)sockfd) )){
              printf("Error creating SendMessage thead\n");
              exit(-1);
    }
    if(!( pthread_create(&threads[0], NULL, ReceiveMessage, (void*)t) )){
            printf("Error creating SendMessage thead\n");
          exit(-1);
     }

    while(1){
		continue;
   //      printf("From %s function\n", __FUNCTION__);
	//	 sleep(2);
    }

             
         
      
	close_socket(sockfd);

	return 0;
}



