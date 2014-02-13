/*
 * File Name:	server_recv_handler.c
 * Author:		Emil Maric
 * Date:		Feb. 6, 2014	 
 *
 * Description:
 * Handles messages received by the 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/socket.h>
#include "shared_constants.h"
#include "server_recv_handler.h"


/* GLOBAL VARIABLES */
typedef void (*State)(struct cb*, struct new_user*, unsigned char*, int*); // Function pointer prototype
State state;	// Holds the state function


/*=============================================================================
 *	parse_msg()
 *-----------------------------------------------------------------------------
 * Description:
 * Read in the payload 
 *
 * Parameters:
 * packet_buff		- Holds the circular buffer implementation
 * header			- Holds the packet header
 * header_count		- How many filled bytes are in 'header' variable
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void parse_msg(struct cb* packet_buff, struct new_user* client_info, unsigned char* header, int* header_count)
{
	PAYLOAD_LENGTH_TYPE payload_length;
	int i;		// Index
	char		letter;

	/* Convert the data stored in 'header' into an integer that we can use. 
	 * Data is assumed to be stored as big Endian. */
	for (i = 0; i < HEADER_LENGTH; i++){
		payload_length = (PAYLOAD_LENGTH_TYPE) ( (( (int)-1 & header[i]) << ((HEADER_LENGTH - i - 1)* 8) ) | payload_length );
	}

	/* Read in the payload from the circular buffer until we have read
	 * the entire payload, or until we empty out the circular buffer, in
	 * which case, we need to fetch more data*/
	i = 0;
	while (i < payload_length && packet_buff->head != packet_buff->tail){
		if ( read_cb(packet_buff, &letter) == -1 ){
/* NEEDS CLEANUP */		pthread_exit(NULL);
		}
		
		printf("%c", letter);
		i++;
	}

	fflush(stdout);		// Flush the output buffer

	/* Message has been completely read.
	 * Prepare for new messages */
	if (i == payload_length){
		printf("\n");
		*header_count = 0;
	}

	state = fetch_msg;
	return;
}


/*=============================================================================
 *	fill_header()
 *-----------------------------------------------------------------------------
 * Description:
 * Fills the 'header' buffer  
 *
 * Parameters:
 * packet_buff		- Holds the circular buffer implementation
 * header			- Holds the packet header
 * header_count		- How many filled bytes are in 'header' variable
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void fill_header(struct cb* packet_buff, struct new_user* client_info, unsigned char* header, int* header_count)
{
	/* Read in from the circular buffer, into the 'header' buffer */
	while (*header_count < HEADER_LENGTH && packet_buff->tail != packet_buff->head ){
		if ( read_cb(packet_buff, (char *)&(header[*header_count])) == -1 ){
/* NEEDS CLEANUP */		pthread_exit(NULL);
		}

		(*header_count)++;
	}

	/* If the header is fully read in, proceed to parse through the payload */
	if (*header_count == HEADER_LENGTH){
		state = parse_msg;
	}
	/* Header is not fully read; we need to fetch more data */
	else {
		state = fetch_msg;
	}

	return;
}


/*=============================================================================
 *	fetch_msg()
 *-----------------------------------------------------------------------------
 * Description:
 * Waits for received messages.
 *
 * Parameters:
 * packet_buff		- Holds the circular buffer implementation
 * header			- Holds the packet header
 * header_count		- How many filled bytes are in 'header' variable
 *
 * Return Value:
 * NONE
 *
 *=============================================================================
 */
void fetch_msg(struct cb* packet_buff, struct new_user* client_info, unsigned char* header, int* header_count)
{
	int space_left;		// space left in the circular buffer before it is full
	int message_length;	// length of the message receieved from the client

	/* Get the number of remaining spaces available in the circular buffer */
	if ((space_left = lenLeft_cb(packet_buff)) == -1 ){
/* NEEDS CLEANUP */
		pthread_exit(NULL);
	}

	/* Place the received message in the circular buffer and store its length in a variable */
	if((message_length = recv(client_info->sockfd, &(packet_buff->buff[packet_buff->head]), space_left, 0)) <= 0){
/* NEEDS CLEANUP */
		pthread_exit(NULL);
	}

	/* Advance the head pointer of the circular buffer to point to the end of
	 * data
	 */
	packet_buff->head = ((packet_buff->head) + message_length) % (packet_buff->size);

	/* Check to see the next state */
	if (*header_count == HEADER_LENGTH){
		state = parse_msg;	
	}
	else {
		state = fill_header;
	}

	return;
}



/*=============================================================================
 *	client_receive_handler()
 *-----------------------------------------------------------------------------
 * Description:
 * Initializes the state machine for receiving messages from the client.
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
	struct cb				packet_buff;
	unsigned char			header[HEADER_LENGTH];
	int						header_count = 0;

	// Initialize the circular buffer
	if ( init_cb(&packet_buff, HEADER_LENGTH + MAX_PACKET_LENGTH) == -1){
/* NEEDS CLEANUP */
		pthread_exit(NULL);
	}

	state = fetch_msg;	// The first state

	while (1){
		state(&packet_buff, client_info, header, &header_count);	
	}

	pthread_exit(NULL);
}
