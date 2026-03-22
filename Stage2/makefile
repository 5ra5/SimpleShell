# relevant directories
SRC_DIR = src
BIN_DIR = bin

# source files - compiled together
SRC = $(SRC_DIR)/simpleshell.c \
      $(SRC_DIR)/utility.c \
	  $(SRC_DIR)/internal_commands.c \
	  $(SRC_DIR)/execute_commands.c \
	  $(SRC_DIR)/external_commands.c

# compiler and flags
CC = gcc
CFLAGS = -Wall -g

# target = binary
TARGET = $(BIN_DIR)/simpleshell

# default taget = binary
all: $(BIN_DIR) $(TARGET)

# create binary = compile with gcc and use relevant flags
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# if there is no bin directory, create it
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# clean up - delete simpleshell binary
clean:
	rm -f $(TARGET)