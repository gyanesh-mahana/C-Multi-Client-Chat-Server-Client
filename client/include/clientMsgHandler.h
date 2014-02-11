/*
 * =====================================================================================
 *
 *       Filename:  clientMsgHandler.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/10/2014 08:16:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "shared_constants.h"

#ifndef CLIENTMSGHANDLER_H
#define CLIENTMSGHANDLER_H

void* SendMessage(void* threadId);
void* ReceiveMessage(void* threadId);
int   sendall( int s, char* buf, int* len);

#endif
