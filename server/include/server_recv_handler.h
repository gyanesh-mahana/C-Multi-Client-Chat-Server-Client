/*
 * File Name:		serverMsgHandler.h
 * Author:			Emil Maric
 * Date Created:	Feb. 6, 2014	 
 *
 * Description:
 * Contains the prototypes for serverMsgHandler.c
 */

#ifndef SERVERMSGHANDLER_H
#define SERVERMSGHANDLER_H

#include "clientProfile.h"
#include "circularBuffer.h"

void *server_recv_handler(void *data);

void fetch_msg(struct cb* packet_buff, struct new_user* client_info, unsigned char* header, int* header_count);

void fill_header(struct cb* packet_buff, struct new_user* client_info, unsigned char* header, int* header_count);

void parse_msg(struct cb* packet_buff, struct new_user* client_info, unsigned char* header, int* header_count);

#endif	// SERVERMSGHANDLER_H
