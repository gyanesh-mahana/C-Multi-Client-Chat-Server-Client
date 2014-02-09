###############################################################################
# Author: 			Emil Maric												  
# Date Created:		Feb. 1, 2014
# Description:		Makefile for compiling the client program.
###############################################################################
.PHONY : all clean SHARED_MAKE

BUILD_DIR 		:= build
INCLUDE_DIR 	:= include
LIB_DIR 		:= lib
SRC_DIR 		:= src
SHARED_DIR		:= ../shared

BIN				:= cclient

SRCS			:= $(wildcard $(SRC_DIR)/*.c)
SRCS			:= $(filter-out $(SRC_DIR)/$(BIN).c, $(SRCS))
OBJECTS			:= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
SHARED_OBJECTS	= $(wildcard $(SHARED_DIR)/$(BUILD_DIR)/*.o)

BIN_OBJECTS		:= $(OBJECTS) $(BUILD_DIR)/$(BIN).o

CC 				:= gcc
CFLAGS 			:= -g -Wall -Werror
CPPFLAGS 		:= -I$(INCLUDE_DIR) -I$(SHARED_DIR)/$(INCLUDE_DIR)
LDFLAGS 		:= -g -lpthread -lm


all: $(BIN)

$(BIN): SHARED_MAKE $(BIN_OBJECTS)
	$(CC) $(CFLAGS) $(BIN_OBJECTS) $(SHARED_OBJECTS) -o $(BIN) $(LDFLAGS) 

$(BUILD_DIR)/$(BIN).o: $(SRC_DIR)/$(BIN).c

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h

$(BIN_OBJECTS):
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	
SHARED_MAKE: FORCE
	make -C ../shared/
	@echo "Shared files built"

clean:
	@-rm -f $(BUILD_DIR)/*.o 
	@-rm -f $(BIN)
	@echo "Clean Finished..."

FORCE:
