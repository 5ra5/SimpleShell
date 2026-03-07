# Petra Sartori, 23324886 - Operating Systems Project Stage 1
# CSC1021/simpleshell

# directories
SRC_DIR = src
BIN_DIR = bin

# source files
SRC = $(SRC_DIR)/simpleshell.c \
      $(SRC_DIR)/utility.c \
	  $(SRC_DIR)/internal_commands.c \
	  $(SRC_DIR)/execute_commands.c

# compiler and flags
CC = gcc
CFLAGS = -Wall -g

# target binary
TARGET = $(BIN_DIR)/simpleshell

# default taget
all: $(BIN_DIR) $(TARGET)

# create binary
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# if there is no bin directory, create it
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# clean up
clean:
	rm -f $(TARGET)