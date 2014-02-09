/*
 * File Name:	shared_constants.h
 * Author:	Emil Maric
 * Date:	Feb. 06, 2014	 
 *
 * Description:
 * Shared constants for the server and clinet.
 */

#ifndef SHAREDCONSTANTS_H
#define SHAREDCONSTANTS_H

#include <math.h>

#define CHATSERVER_PORT			"3490"
#define USERNAME_MAX_LENGTH		20

#define HEADER_PAYLOAD_LENGTH_BITS		16	// MUST BE DEFINED AS ONE OF THE FOLLOWING {8, 16, 24, 32}
#define HEADER_PAYLOAD_LENGTH			HEADER_PAYLOAD_LENGTH_BITS / 8
#define MAX_PAYLOAD_LENGTH				(int) (pow(2, HEADER_PAYLOAD_LENGTH_BITS) - 1)		
#define MAX_PACKET_LENGTH				HEADER_PAYLOAD_LENGTH + MAX_PAYLOAD_LENGTH

// 3 Levels of indirection below to get the correct unsigned integer type.
// Ugly, but a necessary evil.
#define CONCAT(x)						uint ## x ## _t
#define	X_PAYLOAD_TYPE(x)				CONCAT(x)
#define PAYLOAD_LENGTH_TYPE				X_PAYLOAD_TYPE(HEADER_PAYLOAD_LENGTH_BITS)

#endif	// SHAREDCONSTANTS_H
