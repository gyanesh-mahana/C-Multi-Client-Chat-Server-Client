/*
 * File Name:	server_constants.h
 * Author:		Emil Maric
 * Date:		Feb. 8, 2014	 
 *
 * Description:
 * Defines constants used by the server.
 */

#ifndef SERVERCONSTANTS_H
#define SERVERCONSTANTS_H

#include <math.h>

#define BACKLOG		5

#define HEADER_PAYLOAD_LENGTH_BITS		16	// MUST BE DEFINED AS ONE OF THE FOLLOWING {8, 16, 24, 32}
#define HEADER_PAYLOAD_LENGTH			HEADER_PAYLOAD_LENGTH / 8
#define MAX_PAYLOAD_LENGTH				(int) (pow(2, HEADER_PAYLOAD_LENGTH_BITS) - 1)		
#define MAX_PACKET_LENGTH				HEADER_PAYLOAD_LENGTH + MAX_PAYLOAD_LENGTH

// 3 Levels of indirection below to get the correct unsigned integer type.
// Ugly, but a necessary evil.
#define CONCAT(x)						uint ## x ## _t
#define	X_PAYLOAD_TYPE(x)				CONCAT(x)
#define PAYLOAD_LENGTH_TYPE				CONCAT(HEADER_PAYLOAD_LENGTH_BITS)

#endif	// SERVERCONSTANTS_H

