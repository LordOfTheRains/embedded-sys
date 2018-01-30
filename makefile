CC=gcc -g -std=c99
INC_DIR = ./
CFLAGS=-c -Wall -I$(INC_DIR)
DEPS = $(DEPS)*.h

all: lab1

lab1: 
	$(CC) -o lab1 devices.o lab1.c -lm

run:
	./lab1 2 1 10 0

clean:
	rm -rf lab1
