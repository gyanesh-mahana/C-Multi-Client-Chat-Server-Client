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

#define CHATSERVER_PORT		"3490"
#define MAX_PACKET_LENGTH   65537

#define HEADER_PAYLOAD_LENGTH_BITS 16 // MUST BE DEFINED AS ONE OF THE FOLLOWING {8, 16, 24, 32}
#define HEADER_PAYLOAD_LENGTH HEADER_PAYLOAD_LENGTH_BITS / 8

#endif	// SHAREDCONSTANTS_H
