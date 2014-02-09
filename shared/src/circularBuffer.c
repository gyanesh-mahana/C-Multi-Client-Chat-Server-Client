/*
 * File Name:	circularBuffer.c
 * Author:	Emil Maric
 * Date:	Feb. 05, 2014	 
 *
 * Description:
 * Buffer functions for implementing a circular buffer. This type buffer 
 * is used for processing incoming packets.
 */

#include <stdio.h>
#include <stdlib.h>
#include "circularBuffer.h"


/*=============================================================================
 *	init_cb()
 *-----------------------------------------------------------------------------
 * Description:
 * Initializes the circular buffer.
 *
 * Parameters:
 * cbuff	- pointer to a circular buffer
 * size		- size of circular buffer -- ('1' is added to the given size
 *			  because we want an extra slot in our circular buffer. The reason 
 *			  for this is so that we can differentiate between an empty buffer
 *			  and a full buffer)
 *			  Source: http://en.wikipedia.org/wiki/Circular_buffer#Always_Keep_One_Slot_Open
 *
 * RETURN
 * Returns '0' on success, and '-1' on failure.
 *
 *=============================================================================
 */
int init_cb(struct cb *cbuff, int size)
{
	if (!cbuff){
		fprintf(stdout, "ERROR init_cb: received null pointer\n");
		return -1;
	}

	cbuff->tail = 0;
	cbuff->head = 0;
	cbuff->size = size + 1;
	cbuff->buff = (char*) malloc( (cbuff->size) * sizeof(char) );

	// Malloc failed
	if ( !(cbuff->buff) ){
		fprintf(stdout, "ERROR init_cb: malloc() failed to allocate memory\n");
		return -1;
	}

	return 0;
}


/*=============================================================================
 *	write_cb()
 *-----------------------------------------------------------------------------
 * Description:
 * Writes to the current element pointed to by 'head' in the circular buffer
 *
 * Parameters:
 * cbuff	- pointer to a circular buffer
 * letter	- character to write
 *
 * RETURN
 * Returns '0' on success, and '-1' on failure.
 *
 *=============================================================================
*/
int write_cb(struct cb *cbuff, char letter)
{
	if (!cbuff){
		fprintf(stdout, "ERROR write_cb(): received null pointer\n");
		return -1;
	}

	// Check to make sure we are not overwriting data
	if ( full_cb(cbuff) ){
		fprintf(stdout, "Circular Buffer is full. Buffer must be read or cleared.\n");
		return -1;
	}

	cbuff->buff[cbuff->head] = letter;
	cbuff->head = (cbuff->head + 1) % cbuff->size;

	return 0;	
}


/*=============================================================================
 *	read_cb()
 *-----------------------------------------------------------------------------
 * Description:
 * Reads from the current element pointed to by 'tail' in the circular buffer
 *
 * Parameters:
 * cbuff	- pointer to a circular buffer
 * letter	- pointer that will contain the character read from the circular
 *			  buffer
 *
 * RETURN
 * Returns '0' on success, and '-1' on failure.
 *
 *=============================================================================
*/
int read_cb(struct cb *cbuff, char *letter)
{
	if (!cbuff){
		fprintf(stdout, "ERROR read_cb(): received null pointer\n");
		return -1;
	}

	*letter = cbuff->buff[cbuff->tail];
	cbuff->tail = (cbuff->tail + 1) % cbuff->size;

	return 0;
}


/*=============================================================================
 *	full_cb()
 *-----------------------------------------------------------------------------
 * Description:
 * Determines whether or not the circular buffer is full
 *
 * Parameters:
 * cbuff	- pointer to a circular buffer
 *
 * RETURN
 * Returns '1' if circular buffer is full, and '0' if not, and '-1' if there 
 * is an error.
 *
 *=============================================================================
*/
int full_cb(struct cb *cbuff)
{
	if (!cbuff){
		fprintf(stdout, "ERROR full_cb(): received null pointer\n");
		return -1;
	}
	
	return (cbuff->head + 1) % cbuff->size == cbuff->tail % cbuff->size;
}


/*=============================================================================
 *	lenLeft_cb()
 *-----------------------------------------------------------------------------
 * Description:
 * Determines whether or not the circular buffer is full
 *
 * Parameters:
 * cbuff	- pointer to a circular buffer
 *
 * RETURN
 * Returns how many spaces are left in the circular buffer, and '-1' if there 
 * is an error.
 *
 *=============================================================================
*/
int lenLeft_cb(struct cb *cbuff)
{
	if (!cbuff){
		fprintf(stdout, "ERROR full_cb(): received null pointer\n");
		return -1;
	}
	
	if ( cbuff->tail > cbuff->head ){
		return (cbuff->tail) - (cbuff->head);
	}
	else {
		return (cbuff->size) - (cbuff->head);
	}
}
