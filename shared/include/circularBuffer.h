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
 *	struct cb
 *-----------------------------------------------------------------------------
 * Description:
 * Defines the circular buffer structure.
 *
 * Parameters:
 * tail			- tail index of the circular buffer
 * head			- head index of the circular buffer
 * size			- size of the circular buffer
 * buff			- pointer to the character buffer
 *
 *=============================================================================
 */
struct cb {
	int			tail;
	int			head;
	int			size;
	char *		buff;
};


int init_cb(struct cb *cbuff, int size);

int write_cb(struct cb *cbuff, char letter);

int read_cb(struct cb *cbuff, char *letter);

int full_cb(struct cb *cbuff);

int lenLeft_cb(struct cb *cbuff);

#endif	// CIRCULARBUFFER_H
