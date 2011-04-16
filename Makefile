# linkedlist makefile
SHELL=/bin/sh

CC=g++
CFLAGS=-ansi -Wall --pedantic
OBJECTS=src/main.cpp

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o list3

clean:
	rm -f list3

