#!/bin/make
CC=gcc
CFLAGS=-Wall -O2 -pipe
TARGET=monadebug
OBJECTS=bmw.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
