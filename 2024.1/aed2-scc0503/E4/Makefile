CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

SRC_FILES = Graph.c main.c
OBJ_FILES = $(SRC_FILES:.c=.o)
BIN_TARGET = main

.PHONY: all clean

all: $(BIN_TARGET)

$(BIN_TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(BIN_TARGET)

remake: 
	make clean
	make all

run:
	./$(BIN_TARGET)
