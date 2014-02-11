/*
 * =====================================================================================
 *
 *       Filename:  clientMsgHandler.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/10/2014 08:15:43 PM
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
#include <pthread.h>
#include "shared_constants.h"
#include "clientMsgHandler.h"

void* SendMessage(void* threadId)
{
    char packet[MAX_PACKET_LENGTH];
    unsigned char header_size[HEADER_PAYLOAD_LENGTH];
    char* message = "Hello Emil";
    int size = strlen(message);
    int len;
    int i;
    
    len = size + HEADER_PAYLOAD_LENGTH;

    for( i = (HEADER_PAYLOAD_LENGTH-1); i >= 0; --i){
        header_size[i] = (unsigned char)((size|0x0)>>(((HEADER_PAYLOAD_LENGTH-(i+1))*8) & 0xFF) );

    }   
    
    for(i = 0; i < HEADER_PAYLOAD_LENGTH; ++i){
          packet[i] = header_size[i];
    }
   
    strcpy( &packet[i], message);

    sendall(atoi(CHATSERVER_PORT), packet, &len);

    do{ 
        printf("Inside %s\n",__FUNCTION__);
        sleep(2);
    }while(1);

	pthread_exit(NULL);
}

void* ReceiveMessage(void* threadId)
{
    do{ 
    printf("Inside %s\n",__FUNCTION__);
    sleep(2);

    }while(1);

	pthread_exit(NULL);
}


int   sendall( int s, char* buf, int* len)
{
    int total = 0; // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;
    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }
    *len = total; // return number actually sent here
    
    return n==-1?-1:0; // return -1 on failure, 0 on success
}


