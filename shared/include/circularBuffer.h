/*
 * File Name:	circularBuffer.h
 * Author:	Emil Maric
 * Date:	Feb. 06, 2014	 
 *
 * Description:
 * Function prototypes for the circular buffer functions.
 */

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

/*=============================================================================
 *	struct element
 *-----------------------------------------------------------------------------
 * Description:
 * Defines the struct-type for the elements within the circular buffer.
 *
 * Parameters:
 * letter	- holds a letter from the packet 
 *
 *=============================================================================
 */
struct element{
	char letter;
};


/*=============================================================================
 *	struct cb
 *-----------------------------------------------------------------------------
 * Description:
 * Defines the circular buffer structure.
 *
 * Parameters:
 * tail			- tail index of the circular buffer
 * head			- head index of the circular buffer
 * size			- size of the circular buffer
 * elements		- pointer that 
 *				  contains all the elements of the circular buffer
 *
 *=============================================================================
 */
struct cb {
	int					tail;
	int					head;
	int					size;
	struct element*		elements;
};


int init_cb(struct cb *cbuff, int size);

int write_cb(struct cb *cbuff, struct element *elem);

int read_cb(struct cb *cbuff, struct element *elem);

int full_cb(struct cb *cbuff);

#endif	// CIRCULARBUFFER_H
