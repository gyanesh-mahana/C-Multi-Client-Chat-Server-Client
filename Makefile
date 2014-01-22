CC=gcc
CFLAGS=-g -Wall -Werror

cserver: cserver.c cserverApi.o
	$(CC) $(CFLAGS) cserver.c -o cserver cserverApi.o -lpthread

cserverApi.o: cserverApi.c cserverApi.h
	$(CC) $(CFLAGS) -c cserverApi.c -o cserverApi.o -lpthread

