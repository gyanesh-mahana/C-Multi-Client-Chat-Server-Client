###############################################################################
# Author: 			Emil Maric												  
# Date Created:		Feb. 1, 2014
# Description:		Creates objects from shared source files.
###############################################################################
BUILD_DIR 		:= build
INCLUDE_DIR 	:= include
LIB_DIR 		:= lib
SRC_DIR 		:= src

SRCS			:= $(wildcard $(SRC_DIR)/*.c)
OBJECTS			:= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CC := gcc
CFLAGS := -g -Wall -Werror
CPPFLAGS := -I$(INCLUDE_DIR)
LDFLAGS := -g -lpthread -lm

.PHONY : all clean

all: $(OBJECTS)

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	@-rm -f $(BUILD_DIR)/*.o 
	@echo "Clean Finished..."

