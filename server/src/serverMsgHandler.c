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
#include "circularBuffer.h"
#include "serverMsgHandler.h"
#include "server_constants.h"

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
	struct new_user			*client_info = (struct new_user *)data;
	struct cb				packetBuff;
	unsigned char			payloadHeader[HEADER_PAYLOAD_LENGTH];
	int						buffRemaining, msgLen, i;
	int						payload_header_count = 0;
	PAYLOAD_LENGTH_TYPE		payload_length = 0;

	// Initialize the circular buffer
	if ( init_cb(&packetBuff, 2*MAX_PACKET_LENGTH) == -1){
/* NEEDS CLEANUP */
		pthread_exit(NULL);
	}

	while(1) {
		if (buffRemaining = lenLeft_cb(&packetBuff) == -1 ){
/* NEEDS CLEANUP */
			pthread_exit(NULL);
		}

		if(msgLen = recv(client_info->sockfd, packetBuff->buff[packetBuff->head], buffRemaining, NULL) <= 0){
/* NEEDS CLEANUP */
			pthread_exit(NULL);
		}

		// Adjust the head pointer to match the end of the new data
		packetBuff->head = ((packetBuff->head) + msgLen) % (packetBuff->size);

		while(1){

			// If our payloadHeader buffer is not full, try to read the rest in from the circular buffer
			if (payload_header_count != HEADER_PAYLOAD_LENGTH){
				while (payload_header_count < HEADER_PAYLOAD_LENGTH || packetBuff->tail != packetBuff->head ){
					if ( read_cb(&packetBuff, &(payloadHeader[payload_header_count])) == -1 ){
/* NEEDS CLEANUP */		pthread_exit(NULL);
					}

					payload_header_count++;
				}
				
				// If this is true, then the circular buffer is empty. This means that we need to fetch more data.
				if (packetBuff->tail == packetBuff->head){
					break;
				}
			}

			// Convert the char buffer into an integer that we can use
			for (i = 0; i < HEADER_PAYLOAD_LENGTH; i++){
				payload_length = ( ((int) 255 & payloadHeader[i]) << (i * 8) ) | payload_length;
			}

			printf("%i\n", payload_length);

		}
	}

	pthread_exit(NULL);
}
